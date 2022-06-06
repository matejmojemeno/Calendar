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
}

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

int Event::displayFull() const 
{
    clear();
    move(0, 0);

    printw(name.c_str());
    printw(", ");
    printw(place.c_str());
    mvprintw(1, 0, "Start: %02d.%02d.%d %02d:%02d", start.m_day, start.m_mon, start.m_year, start.m_hour, start.m_min);
    mvprintw(2, 0, "End: %02d.%02d.%d %02d:%02d", end.m_day, end.m_mon, end.m_year, end.m_hour, end.m_min);
    move(3, 0);
    for (auto person : participants) {
        printw("%s, ", person.c_str());
    }
    move(4, 0);
    printw("Repetition: %s", getRep(rep).c_str());
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


Event Event::operator+ (int amount)
{
    return Event(start + amount, end + amount, name, place, participants, rep);
}

void Event::exportEvent() const {
    std::ofstream f("out/" + name + ".txt");

    if (! f.is_open() || ! f.good())
        throw std::invalid_argument("Cannot write into file.");
    
    f << "start = " << start.m_day << "." << start.m_mon << "." << start.m_year << " " << start.m_hour << ":" << start.m_min << "\n";
    f << "end = " << end.m_day << "." << end.m_mon << "." << end.m_year << " " << end.m_hour << ":" << end.m_min << "\n";
    f << "name = " << name << "\n";
    f << "place = " << place << "\n";
    f << "participants = ";
    for (auto person : participants)
        f << person << ", ";
    f << "\n" << getRep(rep);
}

std::string Event::getRep(int rep) const {
    if (rep == 0)
        return "never";
    if (rep == 1)
        return "every day";
    if (rep == 2)
        return "every week";
    if (rep == 3)
        return "every 14 days";
    if (rep == 4)
        return "every month";
    return "never";
}