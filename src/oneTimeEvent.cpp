#include "oneTimeEvent.h"

OneTimeEvent::OneTimeEvent(const Time &s, const Time &e, const std::string &n, const std::string &p, const std::vector<std::string> &part, int r)
                : Event(s, e, n, p, part, r) {}

OneTimeEvent::OneTimeEvent(const Event &event) : Event(event){}

bool OneTimeEvent::isSameDay(const Time &time) const
{
    return std::tie(start.m_year, start.m_mon, start.m_day) == std::tie(time.m_year, time.m_mon, time.m_day);
}

bool OneTimeEvent::intersectEvent(const Event &event) const 
{
    if (event.start <= start && start <= event.end)
        return true;
    if (event.start <= end && end <= event.end)
        return true;
    if (start <= event.start && event.start <= end)
        return true;
    if (start <= event.end && event.end <= end)
        return true;
    return false;
}

bool OneTimeEvent::wantToMove(const Time &newStart) const
{
    clear();
    printRequest(newStart);
    int c = getch();
    while(c != '1' && c != '2')
    {
        clear();
        refresh();
        printRequest(newStart);

        c = getch();
    }

    return c == '1';
}

void OneTimeEvent::printRequest(const Time &time) const
{
    if (std::tie(start.m_year, start.m_mon, start.m_mon) == std::tie(time.m_year, time.m_mon, time.m_day)) {
        printw("Event collides with another event.\n");
        printw("1 - move to %02d:%02d, 2 - exit.", time.m_hour, time.m_min);
    }
    else {
        printw("Event collides with another event.\n");
        printw("1 - move to %d.%d.%d %02d:%02d, 2 - exit.", time.m_day, time.m_mon, time.m_year, time.m_hour, time.m_min);
    }
}