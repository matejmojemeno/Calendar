#include "monthlyEvent.h"

MonthlyEvent::MonthlyEvent(const Time &s, const Time &e, const std::string &n, const std::string &p, const std::vector<std::string> &part, int r)
                : Event(s, e, n, p, part, r) 
{
    if (e - s > 4*WEEK)
        throw std::invalid_argument("Event collides with iteself.");
}


MonthlyEvent::MonthlyEvent(const Event &event) : Event(event){}

bool MonthlyEvent::isSameDay(const Time &time) const
{
    if (std::tie(start.m_year, start.m_mon, start.m_day) <= std::tie(time.m_year, time.m_mon, time.m_day))
        return start.m_day == time.m_day;
    return false;
}