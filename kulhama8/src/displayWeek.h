#include "displayDay.h"

class DisplayWeek : public DisplayCalendar
{
public:
    /**
     * @brief 
     * displays days of given week
     */
    void displayDays(const Time &) const override;
    /**
     * @brief 
     * controls displayDay
     */
    void controlDisplay(Time &, const EventStorage &) const override;
    /**
     * @brief 
     * displays events of current day
     */
    void displayEvents(const Time &, const EventStorage &, int &) const;
    void display(const Time &, const EventStorage &, int &) const;
    /**
     * @brief 
     * adjusts position if out of interval
     */
    void adjustPos(int &, const std::vector<Event> &) const;

private:
    DisplayDay day;
};