#include "event.h"

class OneTimeEvent : public Event 
{
public:
    bool isSameDay(const Time &) const override;
};