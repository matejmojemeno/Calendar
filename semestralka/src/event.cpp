#include "event.h"

Event::Event(const Time &s, const Time &e, const std::string &n, const std::string &p, const std::vector<std::string> &part, int r)
{
    start = s;
    end = e;
    name = n;
    place = p;
    participants = part;
    rep = r;

    if (rep < 0 || rep > 4)
        rep = 0;
}

void Event::displaySmall(int line, bool highlighted) const
{
    if (highlighted)
        attron(HIGHLIGHT);
    mvprintw(line, 0, name.c_str());
    mvprintw(line, name.size() + 1, "%02d:%02d", start.m_hour, start.m_min);

    attroff(HIGHLIGHT);
}

void Event::displayFull() const 
{
    clear();
    move(0, 0);

    printw(name.c_str());
    printw(", ");
    printw(place.c_str());
    mvprintw(1, 0, "Start: %02d.%02d.%d %02d:%02d", start.m_day, start.m_mon, start.m_year, start.m_hour, start.m_min);
    mvprintw(2, 0, "End: %02d.%02d.%d %02d:%02d", end.m_day, end.m_mon, end.m_year, end.m_hour, end.m_min);

    getch();
}


Event Event::operator+ (int amount)
{
    return Event(start + amount, end + amount, name, place, participants, rep);
}