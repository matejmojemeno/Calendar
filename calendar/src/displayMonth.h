#include "displayWeek.h"

class DisplayMonth : public Display
{
public:
    /**
     * @brief 
     * displays all components together
     */
    void display(const Time &, const EventStorage &) const override;
    /**
     * @brief 
     * displays all days of month
     */
    void displayDays(const Time &) const override;
private:
    DisplayDay day;
};