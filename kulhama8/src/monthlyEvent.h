#include "twoWeeklyEvent.h"

class MonthlyEvent : public Event {
public:  
    bool isSameDay(const Time &) const override;
};