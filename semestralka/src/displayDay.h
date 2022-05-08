#include "displayCalendar.h"

class DisplayDay : public DisplayCalendar
{

public:
    void displayEvents() const override;

    DisplayDay &moveLeft();
    DisplayDay &moveRight();

private:
    int pos;
};