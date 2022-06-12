#include "displayWeek.h"

class DisplayMonth : public Display
{
public:
    /**
     * @brief 
     * displays all days of month
     */
    void displayDays(const Time &) const override;

    /**
     * @brief 
     * controls displayed days
     */
    void controlDisplay(Time &, const EventStorage &) const override;

private:
    DisplayDay day;
};