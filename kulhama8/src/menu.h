#include <array>
#include <map>
#include <string>
#include <ncurses.h>

#include "displayManager.h"

#define BACK 4
#define EXIT 2

class Menu
{
public:
    /**
     * @brief
     * start menu
     */
    int mainMenu() const;
    /**
     * @brief
     * menu to manage events
     */
    int eventMenu() const;

private:
    /**
     * @brief
     * function to operate chosen menu
     * @return int
     */
    int menu(const std::vector<const char *> &) const;
    /**
     * @brief
     * prints menu to screen
     */
    void displayMenu(const std::vector<const char *>, int) const;
    /**
     * @brief
     * updates position if out of interval
     */
    void updatePos(int, int &, size_t) const;

    static const std::vector<const char *> menuItems;
    static const std::vector<const char *> eventItems;
};