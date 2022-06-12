#include "twoWeeklyEvent.h"

class MonthlyEvent : public Event {
public:  
    MonthlyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    MonthlyEvent(const Event &);
    bool isSameDay(const Time &) const override;
};