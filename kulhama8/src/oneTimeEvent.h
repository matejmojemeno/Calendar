#include "event.h"

class OneTimeEvent : public Event 
{
public:
    OneTimeEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    OneTimeEvent(const Event &);
    bool isSameDay(const Time &) const override;
    bool intersectEvent(const Event &) const;
    bool wantToMove(const Time &) const;
    void printRequest(const Time &) const;
};