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
        mvprintw(2, 3 + 4 * i, "%d", weekDay.m_day);
        attroff(HIGHLIGHT);
        attroff(BLUE);
        weekDay = weekDay + DAY;
    }
}

void DisplayWeek::displayEvents(const Time &time, const EventStorage &events, int &pos) const
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
        eventsList[i + down]->displaySmall(i + 3, highlight);
    }
}

void DisplayWeek::controlDisplay(Time &time, const EventStorage &events) const
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
        if (c == '\n')
            day.controlDisplay(time, events);

        display(time, events, pos);
        c = getch();
    }
}

void DisplayWeek::display(const Time &time, const EventStorage &events, int &pos) const
{
    clear();
    refresh();
    displayHeader(time);
    displayDayNames();
    displayDays(time);
    displayEvents(time, events, pos);
}

void DisplayWeek::adjustPos(int &pos, size_t listSize) const
{
    if (pos < -1)
        pos = -1;
    else if (pos >= static_cast<int>(listSize))
        pos = static_cast<int>(listSize) - 1;
}