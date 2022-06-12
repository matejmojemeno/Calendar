#include "dailyEvent.h"

DailyEvent::DailyEvent(const Time &s, const Time &e, const std::string &n, const std::string &p, const std::vector<std::string> &part, int r)
                : Event(s, e, n, p, part, r) 
{
    if (e - s > DAY)
        throw std::invalid_argument("Event collides with iteself.");
}

DailyEvent::DailyEvent(const Event &event) : Event(event){}

bool DailyEvent::isSameDay(const Time &time) const {
    return std::tie(start.m_year, start.m_mon, start.m_day) <= std::tie(time.m_year, time.m_mon, time.m_day);
}