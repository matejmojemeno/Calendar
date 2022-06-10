#include "twoWeeklyEvent.h"

class MonthlyEvent : public Event {
public:  
    MonthlyEvent(const Event &);
    bool isSameDay(const Time &) const override;
};