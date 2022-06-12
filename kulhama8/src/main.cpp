#include <iostream>
#include <ncurses.h>

#include "calendar.h"

using namespace std;

int main()
{
    Calendar cal;
    cal.startApplication();
    cal.runApplication();
    cal.endApplication();
    return 0;
}