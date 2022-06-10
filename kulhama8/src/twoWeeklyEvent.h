#include "weeklyEvent.h"

class TwoWeeklyEvent : public Event
{
public:
    TwoWeeklyEvent(const Event &);
    bool isSameDay(const Time &) const override;
};