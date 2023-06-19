#include <array>
#include <cstring>
#include <ncurses.h>

#include "eventWrapper.h"

class Display
{
public:
    /**
     * @brief Destroy the Display object
     * virtual destructor
     */
    virtual ~Display();

    virtual void display(const Time &, const EventStorage &) const = 0;

    /**
     * @brief
     * displays month and year
     */
    virtual void displayHeader(const Time &) const;

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
    /**
     * @brief 
     * displays events for given day
     * @param time 
     * @param events 
     */
    virtual void displayEvents(const Time &time, const EventStorage &events) const;

protected:
    static const std::vector<const char *> months;
    static const std::vector<const char *> days;
    static const std::vector<const char *> fullDays;
};