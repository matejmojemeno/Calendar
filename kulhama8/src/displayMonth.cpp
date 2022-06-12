#include "displayMonth.h"

void DisplayMonth::displayDays(const Time &time) const
{
    int day = 1, dayOfWeek = time.dayNumber(time.m_year, time.m_mon, 1);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < DAYS_IN_WEEK; j++)
        {
            if ((i == 0 && j < dayOfWeek) || day > time.monthDays())
                continue;
            if (day == time.m_day)
                attron(COLOR_PAIR(1));
            mvprintw(OFFSET + i, j * DAY_SIZE + OFFSET, "%d", day++);
            attroff(COLOR_PAIR(1));
        }
    }
}

void DisplayMonth::display(const Time &time, const EventStorage &events) const
{
    clear();
    refresh();
    displayHeader(time);
    displayDayNames();
    displayDays(time);
}