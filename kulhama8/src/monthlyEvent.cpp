#include "monthlyEvent.h"

MonthlyEvent::MonthlyEvent(const Event &event) : Event(event){}

bool MonthlyEvent::isSameDay(const Time &time) const
{
    if (std::tie(start.m_year, start.m_mon, start.m_day) <= std::tie(time.m_year, time.m_mon, time.m_day))
        return start.m_day == time.m_day;
    return false;
}