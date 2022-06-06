#include "menu.h"

class Application {
public:
    void startCalendar();
    void endCalendar() const;

private:  
    Controls c;  
    Menu menu;
};