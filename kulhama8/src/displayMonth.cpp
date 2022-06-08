#include "displayMonth.h"

void DisplayMonth::displayDays(const Time &time) const
{
    int day = 1, dayOfWeek = time.dayNumber(time.m_year, time.m_mon, 1);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((i == 0 && j < dayOfWeek) || day > time.monthDays())
                continue;
            if (day == time.m_day)
                attron(COLOR_PAIR(1));
            mvprintw(2 + i, j * 4 + 3, "%d", day++);
            attroff(COLOR_PAIR(1));
        }
    }
}

void DisplayMonth::controlDisplay(Time &time, const EventStorage &events) const
{
    display(time);
    int c = getch();

    while (c != 4)
    {
        if (c == KEY_UP)
            time = time - WEEK;
        else if (c == KEY_DOWN)
            time = time + WEEK;
        else if (c == KEY_RIGHT)
            time = time + DAY;
        else if (c == KEY_LEFT)
            time = time - DAY;
        else if (c == 10)
            day.controlDisplay(time, events);

        display(time);
        c = getch();
    }
}