#include <array>
#include <string>
#include <ncurses.h>

#include "displayMonth.h"

class Menu
{
public:
    void startMenu();
    void eventMenu();
    void displayMenu(const std::array<const char *, 4>, int) const;
    void updatePos(int, int &);

private:
    void callFunc(int);
    void callEventFunc(int);

    static const std::array<const char *, 4> menuItems;
    static const std::array<const char *, 4> eventItems;

    DisplayMonth d;
    DisplayWeek w;
    EventWrapper events;
};