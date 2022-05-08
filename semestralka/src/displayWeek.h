#include "displayCalendar.h"

class DisplayWeek : public DisplayCalendar
{

public:
    void displayDays() const;
    void displayEvents() const override;

    DisplayWeek &moveLeft();
    DisplayWeek &moveRight();

private:
    int pos;
};