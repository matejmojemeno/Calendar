#include <array>
#include <string>
#include <ncurses.h>

class Menu
{
public:
    void startMenu();
    void displayMenu() const;
    void updatePos(int c);

    int pos = 0;
private:
    static const std::array<const char *, 4> menuItems;
};