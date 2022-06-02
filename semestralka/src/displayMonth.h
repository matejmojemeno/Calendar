#include "displayCalendar.h"

class DisplayMonth : public DisplayCalendar
{
public:
    void displayDays(const Time &) const override;

    void controlDisplay(Time &) const;
};