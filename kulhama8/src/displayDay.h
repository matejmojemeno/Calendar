#include "display.h"

class DisplayDay : public Display {
public:
    /**
     * @brief 
     * displays given day
     */
    void displayDays(const Time &) const override;
    /**
     * @brief 
     * controls displayDay
     */
    void controlDisplay(Time &, const EventStorage &) const override;
    /**
     * @brief 
     * displaysEvents on given day
     */
    void displayEvents(const Time &, const EventStorage &, int &) const;
    void display(const Time &, const EventStorage &, int &) const;
    /**
     * @brief 
     * adjusts position if out of interval
     */
    void adjustPos(int &, size_t) const;
};