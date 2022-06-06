#include "eventStorage.h"

void EventStorage::addEvent(const Event &event)
{
    if (!checkName(event.name))
        newName(event);
    else if (checkDate(event) || event.rep)
        insert(event);
    else
    {
        Time newStart = findNewDate(event);
        clear();
        move(0, 0);
        printw("Event collides with another event.");
        printw("Press enter if you want to move it to: %d.%d.%d %02d:%02d", newStart.m_day, newStart.m_mon, newStart.m_year, newStart.m_hour, newStart.m_min);
        int c = getch();
        while (true)
        {
            if (c == 410)
            {
                clear();
                printw("Event collides with another event.");
                printw("Press enter if you want to move it to: %d.%d.%d %02d:%02d", newStart.m_day, newStart.m_mon, newStart.m_year, newStart.m_hour, newStart.m_min);
            }
            if (c == 4) {
                clear();
                break;
            }
            if (c == '\n') {
                moveEvent(event, newStart);
                return;
            }
            c = getch();
        }
    }
}

void EventStorage::removeEvent(const std::string &name)
{
    for (auto event = allEvents.begin(); event != allEvents.end(); event++) {
        if (event->name == name) {
            if (event->rep == 0)
                removeNoRep(name);
            else if (event->rep == 1)
                removeRep(name, dailyEvents);
            else if(event->rep == 2)
                removeRep(name, weeklyEvents);
            else if (event->rep == 3)
                removeRep(name, twoWeeklyEvents);
            else 
                removeRep(name, monthlyEvents);
            allEvents.erase(event);
            break;
        }
    }
}

void EventStorage::removeNoRep(const std::string &name)
{
    for (auto event = eventsByStart.begin(); event != eventsByStart.end(); event++) {
        if (event->name == name) {
            eventsByStart.erase(event);
            break;
        }
    }
    for (auto event = eventsByEnd.begin(); event != eventsByEnd.end(); event++) {
        if (event->name == name) {
            eventsByEnd.erase(event);
            break;
        }
    }
}

void EventStorage::removeRep(const std::string &name, std::vector<Event> &rep)
{
    for (auto event = rep.begin(); event != rep.end(); event++) {
        if (event->name == name) {
            rep.erase(event);
            break;
        }
    }
}

void EventStorage::findName(const std::string &name, bool &found, Event &event) const
{
    for (auto itr : allEvents)
        if (itr.name == name)
        {
            event = itr;
            found = true;
            break;
        }
}

void EventStorage::newName(const Event &event)
{
    Parser p;
    clear();
    move(0, 0);
    printw("Name already taken.");
    mvprintw(1, 0, "Press 1 if you want to pick a new name, 2 if you want to exit.");
    int c = getch();
    while (true)
    {
        if (c == 410)
        {
            clear();
            printw("Name already taken.");
            mvprintw(1, 0, "Press 1 if you want to pick a new name, 2 if you want to exit.");
        }
        if (c == 49)
            break;
        if (c == 50)
            return;
        c = getch();
    }
    std::string newName = p.getString();
    addEvent(Event(event.start, event.end, newName, event.place, event.participants, event.rep));
}

Time EventStorage::findNewDate(const Event &event) const
{
    for (auto itr : eventsByEnd)
    {
        if (itr.end < event.start)
            continue;
        for (auto jtr : eventsByStart)
        {
            if (jtr.end < itr.start)
                continue;
            if (itr.end - jtr.start > event.start - event.end)
                return itr.end;
        }
    }

    return eventsByEnd[eventsByEnd.size() - 1].end;
}

void EventStorage::moveEvent(const Event &event, const Time &newStart)
{
    Time newEnd(event.end);
    long long diff = event.start - newStart;
    newEnd = newEnd + (int) (diff/24/60);
    diff %= (24*60);
    newEnd.m_hour += (int) diff/60;
    diff %= 60;
    newEnd.m_min += (int) diff;
    newEnd.adjustTime();

    insert(Event(newStart, newEnd, event.name, event.place, event.participants, event.rep));
}

bool EventStorage::checkDate(const Event &event) const
{
    for (auto itr : eventsByStart)
    {
        if (intersectEvent(event, itr))
            return false;
    }

    return true;
}

bool EventStorage::checkName(const std::string &name) const
{
    for (auto event : allEvents)
        if (event.name == name)
            return false;
    return true;
}

bool EventStorage::iterateEvents(const Event &event, const std::vector<Event> &eventVector) const
{
    for (auto itr : eventVector)
    {
        if (intersectEvent(event, itr))
            return false;
    }

    return true;
}

bool EventStorage::intersectEvent(const Event &ls, const Event &rs) const
{
    if (rs.start <= ls.start && ls.start <= rs.end)
        return true;
    if (rs.start <= ls.end && ls.end <= rs.end)
        return true;
    return false;
}

void EventStorage::insert(const Event &event)
{
    if (event.rep)
        insertRepeated(event);
    else {
        insertStart(event);
        insertEnd(event);
    }
    allEvents.push_back(event);
}

void EventStorage::insertStart(const Event &event)
{
    if (eventsByStart.empty())
        eventsByStart.push_back(event);
    else
    {
        eventsByStart.insert(std::upper_bound(eventsByStart.begin(), eventsByStart.end(), event, [](Event ls, Event rs)
                                              { return ls.start < rs.start; }),
                             event);
    }
}

void EventStorage::insertEnd(const Event &event)
{
    if (eventsByEnd.empty())
        eventsByEnd.push_back(event);
    else
    {
        eventsByEnd.insert(std::upper_bound(eventsByEnd.begin(), eventsByEnd.end(), event, [](Event ls, Event rs)
                                            { return ls.end < rs.end; }),
                           event);
    }
}

void EventStorage::insertRepeated(const Event &event)
{
    if (event.rep == 1)
    {
        if (event.start - event.end > 24 * 60)
            throw std::invalid_argument("Event collides with itself.");
        dailyEvents.push_back(event);
    }
    else if (event.rep == 2)
    {
        if (event.start - event.end > 7 * 24 * 60)
            throw std::invalid_argument("Event collides with itself.");
        weeklyEvents.push_back(event);
    }
    else if (event.rep == 3)
    {
        if (event.start - event.end > 14 * 24 * 60)
            throw std::invalid_argument("Event collides with itself.");
        twoWeeklyEvents.push_back(event);
    }
    else
    {
        if (event.start - event.end > 28 * 24 * 60)
            throw std::invalid_argument("Event collides with itself.");
        monthlyEvents.push_back(event);
    }
}

std::vector<Event> EventStorage::dayEvents(const Time &time) const
{
    std::vector<Event> dayEvents;
    Time startOfDay = Time(time.m_year, time.m_mon, time.m_day, 23, 59);

    sameDay(dayEvents, startOfDay);
    sameDayReps(dayEvents, startOfDay);
    sameWeekReps(dayEvents, startOfDay);
    sameTwoWeekReps(dayEvents, startOfDay);
    sameMonthReps(dayEvents, startOfDay);

    sort(dayEvents.begin(), dayEvents.end(), [](const Event &ls, const Event &rs)
         { return std::tie(ls.start.m_hour, ls.start.m_min) < std::tie(rs.start.m_hour, rs.start.m_min); });

    return dayEvents;
}

void EventStorage::sameDay(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : eventsByStart)
    {
        if (event.start.m_year == time.m_year && event.start.m_mon == time.m_mon && event.start.m_day == time.m_day)
            dayEvents.push_back(event);
        else if (time + 1 < event.start)
            break;
    }
}

void EventStorage::sameDayReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : dailyEvents)
        if (event.start <= time + 1)
            dayEvents.push_back(event);
}

void EventStorage::sameWeekReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : weeklyEvents)
        if (event.start.dayNumber() == time.dayNumber() && event.start <= time + 1)
            dayEvents.push_back(event);
}

void EventStorage::sameTwoWeekReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : twoWeeklyEvents)
        if (event.start.dayNumber() == time.dayNumber() && event.start.isEvenWeek() == time.isEvenWeek() && event.start <= time + 1)
            dayEvents.push_back(event);
}

void EventStorage::sameMonthReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : monthlyEvents)
        if (event.start.m_day == time.m_day && event.start <= time)
            dayEvents.push_back(event);
}