#include "displayCalendar.h"

class DisplayMonth : public DisplayCalendar
{
public:
    /**
     * @brief Construct a new Display Month object
     * creates instance of class with required position
     */
    DisplayMonth (int currentPos);

    /**
     * @brief 
     * displays days from 1 to maximum days the month has
     */
    void displayDays(const Time &) const override;

    /**
     * @brief 
     * functions to change position based on keyboard input
     * @return DisplayMonth& 
     */
    DisplayMonth &moveLeft();
    DisplayMonth &moveRight();
    DisplayMonth &moveDown();
    DisplayMonth &moveUp();

private:
    int pos;
};
