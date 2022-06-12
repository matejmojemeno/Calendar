#include "displayDay.h"

class DisplayWeek : public Display
{
public:
    /**
     * @brief 
     * displays all components together
     */
    void display(const Time &, const EventStorage &) const override;
    /**
     * @brief 
     * displays days of given week
     */
    void displayDays(const Time &) const override;
};