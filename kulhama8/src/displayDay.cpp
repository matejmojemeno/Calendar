#include "displayDay.h"

void DisplayDay::displayDays(const Time &time) const {
    mvprintw(0, 0, fullDays[time.dayNumber()]);
    mvprintw(1, 0, "%s %d %d", months[time.m_mon], time.m_day, time.m_year);
}

void DisplayDay::displayEvents(const Time &time, const EventStorage &events, int &pos) const
{
    std::vector<Event> eventsList = events.dayEvents(time);
    adjustPos(pos, eventsList);
    int down, maxDepth;
    bool highlight;
    eventsList.size() > 5 ? maxDepth = 5 : maxDepth = eventsList.size();

    for (int i = 0; i < maxDepth; i++)
    {
        pos > 4 ? down = pos - 4 : down = 0;
        i + down == pos ? highlight = true : highlight = false;
        eventsList[i + down].displaySmall(i + 2, highlight);
    }
}

void DisplayDay::controlDisplay(Time &time, const EventStorage &events) const
{
    int pos = -1;
    display(time, events, pos);
    int c = getch();

    while (c != 4)
    {
        if (c == KEY_UP)
            pos--;
        else if (c == KEY_DOWN)
            pos++;
        if (c == KEY_RIGHT && pos == -1)
            time = time + 1;
        else if (c == KEY_LEFT && pos == -1)
            time = time - 1;

        display(time, events, pos);
        c = getch();
    }
}

void DisplayDay::display(const Time &time, const EventStorage &events, int &pos) const
{
    clear();
    refresh();
    displayDays(time);
    displayEvents(time, events, pos);
}

void DisplayDay::adjustPos(int &pos, const std::vector<Event> &events) const
{
    if (pos < -1)
        pos = -1;
    else if (pos >= (int)events.size())
        pos = events.size() - 1;
}