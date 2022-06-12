#include "weeklyEvent.h"

class TwoWeeklyEvent : public Event
{
public:
    TwoWeeklyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    TwoWeeklyEvent(const Event &);
    bool isSameDay(const Time &) const override;
};