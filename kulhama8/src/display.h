#include <array>
#include <cstring>
#include <ncurses.h>

#include "eventWrapper.h"

#define BACK 4

class Display
{
public:
    /**
     * @brief Destroy the Display object
     * virtual destructor
     */
    virtual ~Display();
    
    virtual void display(const Time &) const;

    /**
     * @brief
     * displays month and year
     */
    virtual void displayHeader(const Time &) const;

    /**
     * @brief
     * displays chosen events
     */
    //virtual void displayEvents() const;

    /**
     * @brief
     * displays days from Sunday to Saturday above dates
     */
    virtual void displayDayNames() const;

    /**
     * @brief
     * displays days depending on mode of calendar
     */
    virtual void displayDays(const Time &) const = 0;

    virtual void controlDisplay(Time &, const EventStorage &) const = 0;

protected:
    static const std::vector<const char *> months;
    static const std::vector<const char *> days;
    static const std::vector<const char *> fullDays;
};