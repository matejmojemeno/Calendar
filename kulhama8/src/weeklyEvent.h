#include "dailyEvent.h"

class WeeklyEvent : public Event {
public:
    WeeklyEvent(const Event &);
    bool isSameDay(const Time &) const override;
};