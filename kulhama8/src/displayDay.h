#include "displayCalendar.h"

class DisplayDay : public DisplayCalendar {
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
    void adjustPos(int &, const std::vector<Event> &) const;
};