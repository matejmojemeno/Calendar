#include "twoWeeklyEvent.h"

bool TwoWeeklyEvent::isSameDay(const Time &time) const 
{
    if (std::tie(start.m_year, start.m_mon, start.m_day) <= std::tie(time.m_year, time.m_mon, time.m_day))
        return !((start - time)%(2*WEEK));
    return false;
}