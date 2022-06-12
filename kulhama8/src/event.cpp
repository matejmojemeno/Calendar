#include "event.h"

Event::Event()
{
    std::vector<std::string> emptyVector;
    start = Time();
    end = Time();
    name = "";
    place = "";
    participants = emptyVector;
    rep = 0;

    if (end < start)
        throw std::invalid_argument("Event cannot end before it started.");
}

Event::Event(const Time &s, const Time &e, const std::string &n, const std::string &p, const std::vector<std::string> &part, int r)
{
    start = s;
    end = e;
    name = n;
    place = p;
    participants = part;
    rep = r;

    if (rep < NEVER || rep > MONTHLY)
        rep = 0;
}

Event::Event(const Event &event)
{
    start = event.start;
    end = event.end;
    name = event.name;
    place = event.place;
    participants = event.participants;
    rep = event.rep;
}

Event::~Event() = default;

bool Event::operator==(const Event &event) const
{
    return std::tie(start, end, name, place, participants, rep) == std::tie(event.start, event.end, event.name, event.place, event.participants, event.rep);
}

void Event::move(const Time &newStart)
{
    end = end + (newStart - start);
    start = newStart;
}

void Event::displaySmall(int line, bool highlighted) const
{
    if (highlighted)
        attron(HIGHLIGHT);
    mvprintw(line, 0, name.c_str());
    mvprintw(line, name.size() + 1, "%02d:%02d", start.m_hour, start.m_min);

    attroff(HIGHLIGHT);
}

int Event::displayFull() const 
{
    clear();
    //move(0, 0);

    printw(name.c_str());
    printw(", ");
    printw(place.c_str());
    mvprintw(1, 0, "Start: %02d.%02d.%d %02d:%02d", start.m_day, start.m_mon, start.m_year, start.m_hour, start.m_min);
    mvprintw(2, 0, "End: %02d.%02d.%d %02d:%02d", end.m_day, end.m_mon, end.m_year, end.m_hour, end.m_min);
    //move(3, 0);
    for (auto person : participants) {
        printw("%s, ", person.c_str());
    }
    //move(4, 0);
    printw("\nPress 1 - export, 2 - remove, 3 - move");

    int c = getch();
    while (c != 4) {
        refresh();
        if (c == '1')
            return c;  
        else if (c == '2')
            return c; 
        else if (c == '3')
            return c;
        c = getch();
    }

    return 0;
}

void Event::exportEvent() const {
    std::ofstream f("examples/" + name + ".txt");

    if (! f.is_open() || ! f.good())
        throw std::invalid_argument("Cannot write into file.");
    
    f << "start = " << start.m_day << "." << start.m_mon << "." << start.m_year << " " << start.m_hour << ":" << start.m_min << "\n";
    f << "end = " << end.m_day << "." << end.m_mon << "." << end.m_year << " " << end.m_hour << ":" << end.m_min << "\n";
    f << "name = " << name << "\n";
    f << "place = " << place << "\n";
    f << "participants = ";
    for (auto person : participants)
        f << person << ", ";
}