#include <array>
#include <string>

#include "controls.h"

class Menu
{
public:
    void displayMenu() const;

    Menu &moveUp();
    Menu &moveDown();

private:
    int pos = 0;
    static const std::array<std::string, 4> menuItems;
};