#include "dailyEvent.h"

bool DailyEvent::isSameDay(const Time &time) const {
    return std::tie(start.m_year, start.m_mon, start.m_day) <= std::tie(time.m_year, time.m_mon, time.m_day);
}