#include "event.h"

Event::Event(const Time s, const Time e, std::string n, std::string p, std::vector<std::string> part)
    : start(s), end(e), name(n), place(p), participants(part) {}

void Event::displaySmall(int line, bool highlighted) const
{
    if (highlighted)
        attron(highlight);
    mvprintw(line, 0, name.c_str());
    mvprintw(line, name.size() + 1, "%02d:%02d", start.m_hour, start.m_min);

    attroff(highlight);
}