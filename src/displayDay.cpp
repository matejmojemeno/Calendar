#include "displayDay.h"

void DisplayDay::displayDays(const Time &time) const {
    mvprintw(0, 0, fullDays[time.dayNumber()]);
    mvprintw(1, 0, "%s %d %d", months[time.m_mon], time.m_day, time.m_year);
}

void DisplayDay::display(const Time &time, const EventStorage &events) const
{
    clear();
    refresh();
    displayDays(time);
    displayEvents(time, events);
}