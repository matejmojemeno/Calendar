#include "application.h"

void Application::startCalendar() {
    c.initNcurses();
    menu.startMenu();
    c.endNcurses();
}