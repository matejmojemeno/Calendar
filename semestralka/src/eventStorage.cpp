#include "eventStorage.h"

void EventStorage::addEvent(const Event &event)
{
    if (!checkName(event.name))
        newName(event);
    else if (checkDate(event))
        insert(event);
    else
    {
        clear();
        move(0, 0);
        printw("Pick another date.");
        getch();
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
    printw("Press 1 if you want to pick a new name, 2 if you want to exit.");
    int c = getch();
    while (true)
    {
        if (c == 49)
            break;
        if (c == 50)
            return;
        c = getch();
    }
    std::string newName = p.getString();
    addEvent(Event(event.start, event.end, newName, event.place, event.participants, event.rep));
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
    else
        insertStart(event);
    allEvents.push_back(event);
}

void EventStorage::insertStart(const Event &event)
{
    if (eventsByStart.empty())
        eventsByStart.push_back(event);
    else
    {
        eventsByStart.insert(std::upper_bound(eventsByStart.begin(), eventsByStart.end(), event, [](Event ls, Event rs)
                                              { return ls.start < rs.start; }), event);
    }
}

void EventStorage::insertRepeated(const Event &event)
{
    if (event.rep == 1)
        dailyEvents.push_back(event);
    else if (event.rep == 2)
        weeklyEvents.push_back(event);
    else if (event.rep == 3)
        twoWeeklyEvent.push_back(event);
    else
        monthlyEvents.push_back(event);
}

std::vector<Event> EventStorage::dayEvents(const Time &time) const
{
    std::vector<Event> dayEvents;
    Time startOfDay = Time(time.m_year, time.m_mon, time.m_day, 0, 0);

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
        if (event.start <= time)
            dayEvents.push_back(event);
}

void EventStorage::sameWeekReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : weeklyEvents)
        if (event.start.dayNumber() == time.dayNumber() && event.start <= time)
            dayEvents.push_back(event);
}

void EventStorage::sameTwoWeekReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : twoWeeklyEvent)
        if ((!(event.start - time) % 14) && event.start <= time)
            dayEvents.push_back(event);
}

void EventStorage::sameMonthReps(std::vector<Event> &dayEvents, const Time &time) const
{
    for (auto event : monthlyEvents)
        if (event.start.m_day == time.m_day && event.start <= time)
            dayEvents.push_back(event);
}