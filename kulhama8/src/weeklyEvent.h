#include "dailyEvent.h"

class WeeklyEvent : public Event {
public:
    bool isSameDay(const Time &) const override;
};