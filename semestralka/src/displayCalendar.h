#include <array>
#include <cstring>
#include <ncurses.h>

#include "time.h"

class DisplayCalendar
{
public:
    void display(const Time &) const;

    /**
     * @brief
     * displays month and year
     */
    virtual void displayHeader(const Time &) const;

    /**
     * @brief
     * displays chosen events
     */
    virtual void displayEvents() const;

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

private:
    static const std::array<const char *, 12> months;
    static const std::array<const char *, 7> days;

    // int lenYear(int) const;
};