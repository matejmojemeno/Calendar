#include "event.h"

class OneTimeEvent : public Event 
{
public:
    OneTimeEvent(const Event &);
    bool isSameDay(const Time &) const override;
    bool intersectEvent(const Event &) const;
    bool wantToMove(const Time &) const;
    void printRequest(const Time &) const;
};