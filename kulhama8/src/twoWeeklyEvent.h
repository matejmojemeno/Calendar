#include "weeklyEvent.h"

class TwoWeeklyEvent : public Event
{
public:
    bool isSameDay(const Time &) const override;
};