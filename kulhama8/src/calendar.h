#include "menu.h"

class Calendar {
public:
    /**
     * @brief 
     * prepares application
     */
    void startApplication() const;
    /**
     * @brief 
     * main program manager
     */
    void runApplication();
    /**
     * @brief 
     * prepares program for exit
     */
    void endApplication() const;

private:  
    /**
     * @brief 
     * runs main menu of the calendar
     */
    void runMainMenu();
    /**
     * @brief 
     * runs event menu of the calendar
     */
    void runEventMenu();
    /**
     * @brief 
     * calls function based of position in main menu when enter pressed
     */
    void callMainMenuFunc(int);
    /**
     * @brief 
     * the same but event menu
     */
    void callEventMenuFunc(int);

    EventWrapper events;
    DisplayManager display;
};