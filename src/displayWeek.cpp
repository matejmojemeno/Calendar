#include "displayWeek.h"

void DisplayWeek::displayDays(const Time &time) const
{
    Time weekDay = time - time.dayNumber()*DAY;

    for (int i = 0; i < 7; i++)
    {
        if (weekDay == time)
            attron(HIGHLIGHT);
        if (weekDay.m_mon != time.m_mon)
            attron(BLUE);
        mvprintw(2, OFFSET + DAY_SIZE * i, "%d", weekDay.m_day);
        attroff(HIGHLIGHT);
        attroff(BLUE);
        weekDay = weekDay + DAY;
    }
}

void DisplayWeek::display(const Time &time, const EventStorage &events) const
{
    clear();
    refresh();
    displayHeader(time);
    displayDayNames();
    displayDays(time);
    displayEvents(time, events);
}