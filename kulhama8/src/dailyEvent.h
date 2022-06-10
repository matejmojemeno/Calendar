#include "oneTimeEvent.h"

class DailyEvent : public Event 
{
public:
    DailyEvent(const Event &);
    bool isSameDay(const Time &) const override; 
};