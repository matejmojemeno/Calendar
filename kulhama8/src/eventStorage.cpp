#include "eventStorage.h"

void EventStorage::addEvent(const Event &event)
{
    if (event.rep == NEVER)
        addOneTime(event);
    else
        addRep(event);
}

void EventStorage::addOneTime(const OneTimeEvent &event)
{
    if (checkDate(event))
        insertNoRep(event);
    else
    {
        OneTimeEvent copy = event;
        Time newStart = findNewStart(copy);
        if (copy.wantToMove(newStart))
        {
            copy.move(newStart);
            insertNoRep(copy);
        }
    }
}

void EventStorage::addRep(const Event &event)
{
    if (event.rep == DAILY)
        allEvents.push_back(std::make_shared<DailyEvent>(event));
    else if (event.rep == WEEKLY)
        allEvents.push_back(std::make_shared<WeeklyEvent>(event));
    else if (event.rep == TWOWEEKLY)
        allEvents.push_back(std::make_shared<TwoWeeklyEvent>(event));
    else
        allEvents.push_back(std::make_shared<MonthlyEvent>(event));
}

void EventStorage::insertNoRep(const Event &event)
{
    allEvents.push_back(std::make_shared<OneTimeEvent>(event));

    std::shared_ptr<OneTimeEvent> event_ptr = std::make_shared<OneTimeEvent>(event);
    insertByStart(event_ptr);
    insertByEnd(event_ptr);
}

void EventStorage::insertByStart(const std::shared_ptr<OneTimeEvent> &event)
{
    if (eventsByStart.empty())
        eventsByStart.push_back(event);
    else
    {
        eventsByStart.insert(std::upper_bound(eventsByStart.begin(), eventsByStart.end(), event, [](std::shared_ptr<OneTimeEvent> ls, std::shared_ptr<OneTimeEvent> rs)
                                              { return ls->start < rs->start; }),
                             event);
    }
}

void EventStorage::insertByEnd(const std::shared_ptr<OneTimeEvent> &event)
{
    if (eventsByEnd.empty())
        eventsByEnd.push_back(event);
    else
    {
        eventsByEnd.insert(std::upper_bound(eventsByEnd.begin(), eventsByEnd.end(), event, [](std::shared_ptr<OneTimeEvent> ls, std::shared_ptr<OneTimeEvent> rs)
                                            { return ls->end < rs->end; }),
                           event);
    }
}

bool EventStorage::checkDate(const OneTimeEvent &event) const
{
    for (auto i : eventsByStart)
        if (i->intersectEvent(event))
            return false;
    return true;
}

Time EventStorage::findNewStart(const OneTimeEvent &event) const
{
    for (auto i = 0; i < eventsByEnd.size() - 1; i++)
    {
        Time newStart = eventsByEnd[i]->end + 1;
        if (newStart == eventsByEnd[i + 1]->end || newStart < event.start)
            continue;
        Time next = nextStart(newStart) - 1;

        if (next - newStart > event.end - event.start)
            return newStart;
    }

    return eventsByEnd[eventsByEnd.size() - 1]->end + 1;
}

Time EventStorage::nextStart(const Time &tmpEnd) const
{
    for (auto i : eventsByStart)
        if (tmpEnd <= i->start)
            return i->start;
    return eventsByStart[eventsByStart.size()]->start + 1;
}

std::vector<std::shared_ptr<Event>> EventStorage::findName(const std::string &name) const
{
    std::vector<std::shared_ptr<Event>> sameNameEvents;

    for (auto event : allEvents)
        if (event->name == name)
            sameNameEvents.push_back(event);

    sort(sameNameEvents.begin(), sameNameEvents.end(), [](const Event *ls, const Event *rs)
         { return ls->start < rs->start; });

    return sameNameEvents;
}

std::vector<std::shared_ptr<Event>> EventStorage::findPlace(const std::string &place) const
{
    std::vector<std::shared_ptr<Event>> samePlaceEvents;

    for (auto event : allEvents)
        if (event->place == place)
            samePlaceEvents.push_back(event);

    sort(samePlaceEvents.begin(), samePlaceEvents.end(), [](const Event *ls, const Event *rs)
         { return ls->start < rs->start; });

    return samePlaceEvents;
}

void EventStorage::removeEvent(const std::shared_ptr<Event> event)
{
    removeAll(event);
    if (event->rep == NEVER) {
        removeByStart(*event);
        removeByEnd(*event);
    }
}

void EventStorage::removeAll(const std::shared_ptr<Event> event)
{
    for (auto itr = allEvents.begin(); itr != allEvents.end(); itr++)
        if (*itr == event)
        {
            allEvents.erase(itr);
            break;
        }
}

void EventStorage::removeByStart(const Event &event)
{
    for (auto itr = eventsByStart.begin(); itr != eventsByStart.end(); itr++)
        if (**itr == event)
        {
            eventsByStart.erase(itr);
            break;
        }
}

void EventStorage::removeByEnd(const Event &event)
{
    for (auto itr = eventsByEnd.begin(); itr != eventsByEnd.end(); itr++)
        if (**itr == event)
        {
            eventsByEnd.erase(itr);
            break;
        }
}

bool EventStorage::moveEvent(std::shared_ptr<Event> event, const Time &newStart)
{
    removeEvent(event);
    bool moved = true;

    if (! checkDate(*event) && event->rep == NEVER)
        moved = false;
    else
        event->move(newStart);

    addEvent(*event);
    return moved;
}