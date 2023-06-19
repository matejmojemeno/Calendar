#include "display.h"

class DisplayDay : public Display {
public:
    /**
     * @brief 
     * displays all components together
     */
    void display(const Time &, const EventStorage &) const override;
    /**
     * @brief 
     * displays given day
     */
    void displayDays(const Time &) const override;
};