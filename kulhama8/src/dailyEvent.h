#include "oneTimeEvent.h"

class DailyEvent : public Event 
{
public:
    DailyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    DailyEvent(const Event &);
    bool isSameDay(const Time &) const override; 
};