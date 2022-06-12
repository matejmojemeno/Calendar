#include "dailyEvent.h"

class WeeklyEvent : public Event {
public:
    WeeklyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    WeeklyEvent(const Event &);
    bool isSameDay(const Time &) const override;
};