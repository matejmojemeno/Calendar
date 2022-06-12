#include "menu.h"

//main menu items
#define DISPLAY 0
#define EVENT 1
#define EXIT 2

#define ADD 0
#define IMPORT 1
#define FIND_NAME 2
#define FIND_PLACE 3

class Calendar {
public:
    void startApplication() const;
    void runApplication();
    void endApplication() const;

private:  
    void runMainMenu();
    void runEventMenu();
    void callMainMenuFunc(int);
    void callEventMenuFunc(int);

    EventWrapper events;
    DisplayManager display;
};