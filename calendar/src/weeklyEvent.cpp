#include "weeklyEvent.h"

WeeklyEvent::WeeklyEvent(const Time &s, const Time &e, const std::string &n, const std::string &p, const std::vector<std::string> &part, int r)
                : Event(s, e, n, p, part, r) 
{
    if (e - s > WEEK)
        throw std::invalid_argument("Event collides with iteself.");
}

WeeklyEvent::WeeklyEvent(const Event &event) : Event(event){}

bool WeeklyEvent::isSameDay(const Time &time) const 
{
    if (std::tie(start.m_year, start.m_mon, start.m_day) <= std::tie(time.m_year, time.m_mon, time.m_day))
        return start.dayNumber() == time.dayNumber();
    return false;
}