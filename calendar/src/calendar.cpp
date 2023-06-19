#include "calendar.h"

void Calendar::startApplication() const
{
    Controls c;
    c.initNcurses();
}

void Calendar::endApplication() const
{
    Controls c;
    c.endNcurses();
}

void Calendar::runApplication() 
{
    runMainMenu();
}

void Calendar::runMainMenu()
{
    Menu menu;
    int menuItem = menu.mainMenu();

    while (menuItem != 10 && menuItem != 2)
    {
        callMainMenuFunc(menuItem);


        menuItem = menu.mainMenu();
    }
}

void Calendar::runEventMenu()
{
    Menu menu;
    int menuItem = menu.eventMenu();

    while (menuItem != BACK)
    {
        callEventMenuFunc(menuItem);

        menuItem = menu.eventMenu();
    }
}

void Calendar::callMainMenuFunc(int item)
{
    if (item == DISPLAY)
        display.display(events.storage);
    else if(item == EVENT)
        runEventMenu();
}

void Calendar::callEventMenuFunc(int item)
{
    if (item == ADD)
        events.newEvent();
    else if (item == IMPORT) {
        try {
            events.newFileEvent();
        }
        catch(std::invalid_argument &ia) {
            clear();
            printw("Invalid file format.\nPress a key to continue.");
            getch();
            clear();
        }
    }
    else if (item == FIND_NAME) {
        std::vector<std::shared_ptr<Event>> nameEvents = events.eventsByName();
        events.manageEvents(nameEvents);
    }
    else if (item == FIND_PLACE) {
        std::vector<std::shared_ptr<Event>> placeEvents = events.eventsByPlace();
        events.manageEvents(placeEvents);
    }
        
}