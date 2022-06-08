#include "event.h"

class DailyEvent : public Event 
{
public:
    bool isSameDay(const Time &) const override; 
};