#include "eventWrapper.h"

const std::array<std::string, 4> EventWrapper::repMenu = {" Every day ", " Every week ", " Every two weeks ", " Every month "};

void EventWrapper::getEvent()
{
    printw("Enter an event:");
    Time start = getStart(), end = getEnd();
    checkEventTime(start, end);
    std::string name = getName(), place = getPlace();
    std::vector<std::string> participants = getParticipants();
    getRepetition();

    Event event(start, end, name, place, participants);
}

Time EventWrapper::getStart() const
{
    Parser p;
    mvprintw(1, 0, "Start of the event: ");
    Time time = p.parseDate();

    return time;
}

Time EventWrapper::getEnd() const
{
    Parser p;
    printw("End of the event: ");

    return p.parseDate();
}

std::string EventWrapper::getName() const
{
    Parser p;
    printw("Name of the event: ");

    return p.parseName();
}

std::string EventWrapper::getPlace() const
{
    Parser p;
    printw("Place of the event: ");

    return p.parsePlace();
}

std::vector<std::string> EventWrapper::getParticipants() const
{
    Parser p;
    printw("Participants: ");

    return p.parseParticipants();
}

void EventWrapper::checkEventTime(const Time &start, const Time &end) const
{
    if (end < start)
        throw std::invalid_argument("Event cannot end before it started.");
}

void EventWrapper::resetLine() const
{
    int x, y;
    getyx(stdscr, x, y);
    move(x, 0);
    clrtoeol();
}

void EventWrapper::drawRepMenu(const int pos) const
{
    for (int i = 0; i < 4; i++)
    {
        if (i == pos)
            attron(COLOR_PAIR(1));
        printw(repMenu[i].c_str());
        attroff(COLOR_PAIR(1));
    }
}

int EventWrapper::getRepetition() const
{
    int pos = 0;
    drawRepMenu(0);

    int c = getch();
    while (c != 10)
    {
        updatePos(c, pos);
        resetLine();
        drawRepMenu(pos);

        c = getch();
    }

    return pos;
}

void EventWrapper::updatePos(const int c, int &pos) const
{
    if (c == KEY_LEFT)
        pos--;
    else if (c == KEY_RIGHT)
        pos++;

    pos = (pos + 4) % 4;
}