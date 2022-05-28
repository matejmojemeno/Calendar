#include "displayMonth.h"

void DisplayMonth::displayDays(const Time &time) const
{
     int day = 1, dayOfWeek = time.dayNumber(time.m_year, time.m_mon, 1);

     for (int i = 0; i < 6; i++) {
         for (int j = 0; j < 7; j++) {
            if ((i == 0 && j < dayOfWeek) || day > time.monthDays())
                continue;
            if (day == time.m_day)
                attron(COLOR_PAIR(1));
            mvprintw(2 + i, j*4 + 3, "%d", day);
            attroff(COLOR_PAIR(1));
         }
     }
}

void DisplayMonth::controlDisplay() const
{
    Time time;

    display(time);
    int c = getch();

    while (c != 10) {
        if (c == KEY_UP)
            time = time - 7;
        else if (c == KEY_DOWN)
            time = time + 7;
        else if (c == KEY_RIGHT)
            time = time + 1;
        else if (c == KEY_LEFT)
            time = time - 1;
    } 
}