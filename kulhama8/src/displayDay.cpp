#include "displayDay.h"

void DisplayDay::displayDays(const Time &time) const {
    mvprintw(0, 0, fullDays[time.dayNumber()]);
    mvprintw(1, 0, "%s %d %d", months[time.m_mon], time.m_day, time.m_year);
}

void DisplayDay::displayEvents(const Time &time, const EventStorage &events, int &pos) const
{
    std::vector<std::shared_ptr<Event>> eventsList = events.dayEvents(time);
    adjustPos(pos, eventsList.size());
    int down, maxDepth;
    bool highlight;
    eventsList.size() > 5 ? maxDepth = 5 : maxDepth = eventsList.size();

    for (int i = 0; i < maxDepth; i++)
    {
        pos > 4 ? down = pos - 4 : down = 0;
        i + down == pos ? highlight = true : highlight = false;
        eventsList[i + down]->displaySmall(i + 2, highlight);
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
            time = time + DAY;
        else if (c == KEY_LEFT && pos == -1)
            time = time - DAY;

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

void DisplayDay::adjustPos(int &pos, size_t listSize) const
{
    if (pos < -1)
        pos = -1;
    else if (pos >= static_cast<int>(listSize))
        pos = static_cast<int>(listSize) - 1;
}