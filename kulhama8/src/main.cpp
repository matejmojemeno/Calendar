#include <iostream>
#include <assert.h>
#include <ncurses.h>

#include "calendar.h"

using namespace std;

int main()
{
    Calendar cal;
    cal.startApplication();
    cal.runApplication();
    cal.endApplication();

    try{
        Time(-1,1,1,10,10);
        assert ( "No exception thrown!" == nullptr );
    }
    catch(...) {};

    Time start(2022, 6, 13, 10, 0);
    Time end(2022, 6, 12, 13, 0);
    std::string name = "zacne";
    std::string place = "skor";
    std::vector<std::string> participants = {"ako", "skonci"};
    
    try{
        OneTimeEvent(start, end, name, place, participants, 0);
        assert ( "No exception thrown!" == nullptr );
    }
    catch(...) {};

    return 0;
}