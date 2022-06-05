#include "displayCalendar.h"

class DisplayDay : public DisplayCalendar {
public:
    void displayDays(const Time &) const override;
    void controlDisplay(Time &, const EventStorage &) const override;
    void displayEvents(const Time &, const EventStorage &, int &) const;
    void display(const Time &, const EventStorage &, int &) const;
    void adjustPos(int &, const std::vector<Event> &) const;
};