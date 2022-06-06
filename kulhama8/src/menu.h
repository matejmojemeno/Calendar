#include <array>
#include <string>
#include <ncurses.h>

#include "displayMonth.h"

class Menu
{
public:
    /**
     * @brief 
     * start menu
     */
    void startMenu();
    /**
     * @brief 
     * menu to manage events
     */
    void eventMenu();
    /**
     * @brief 
     * prints menu to screen
     */
    void displayMenu(const std::array<const char *, 4>, int) const;
    /**
     * @brief 
     * updates position if out of interval
     */
    void updatePos(int, int &);

    /**
     * @brief 
     * displays an error messaage
     */
    void exception(std::invalid_argument &) const;

private:
    /**
     * @brief 
     * calls function picked in start menu
     */
    void callFunc(int);
    /**
     * @brief 
     * calls function picked in event menu
     */
    void callEventFunc(int);

    static const std::array<const char *, 4> menuItems;
    static const std::array<const char *, 4> eventItems;

    DisplayMonth d;
    DisplayWeek w;
    EventWrapper events;
};