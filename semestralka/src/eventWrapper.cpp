#include "eventWrapper.h"

const std::array<std::string, 5> EventWrapper::repMenu = {" Never ", " Every day ", " Every week ", " Every two weeks ", " Every month "};

void EventWrapper::getEvent()
{
    clear();
    move(0,0);
    printw("Enter an event:");
    Time start = getStart(), end = getEnd();
    checkEventTime(start, end);
    std::string name = getName(), place = getPlace();
    std::vector<std::string> participants = getParticipants();
    int rep = getRepetition();

    Event event(start, end, name, place, participants, rep);
    storage.addEvent(event);
}

Time EventWrapper::getStart() const
{
    mvprintw(1, 0, "Start of the event: ");
    Time time = p.parseDate();

    return time;
}

Time EventWrapper::getEnd() const
{
    printw("End of the event: ");

    return p.parseDate();
}

std::string EventWrapper::getName() const
{
    printw("Name of the event: ");

    return p.getString();
}

std::string EventWrapper::getPlace() const
{
    printw("Place of the event: ");

    return p.getString();
}

std::vector<std::string> EventWrapper::getParticipants() const
{
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
    for (int i = 0; i < 5; i++)
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

    pos = (pos + 5) % 5;
}

void EventWrapper::getFileEvent() {
    std::string fileName = p.getString(), key, name, place;
    Time start, end;
    std::vector<std::string> participants;
    int rep = -1;
    bool startFlag = false, endFlag = false, nameFlag = false, placeFlag = false, partFlag = false, repFlag = false;

    std::ifstream f(fileName);

    if (! f.is_open() || ! f.good())
        throw std::invalid_argument("xd");
    
    getch();

    while(f >> key) {
        if (! strcasecmp(key.c_str(), "start") && !startFlag) {
            start = getFileTime(f);
            startFlag = true;
        }
        else if (! strcasecmp(key.c_str(), "end") && !endFlag) {
            end = getFileTime(f);
            endFlag = true;
        }
        else if (! strcasecmp(key.c_str(), "name") && !nameFlag) {
            name = getFileString(f);
            nameFlag = true;
        }
        else if (! strcasecmp(key.c_str(), "place") && !placeFlag) {
            place = getFileString(f);
            placeFlag = true;
        }
        else if (! strcasecmp(key.c_str(), "participants") && !partFlag) {
            participants = getFilePart(f);
            partFlag = true;
        }
        else if (! strcasecmp(key.c_str(), "repetition") && !repFlag) {
            rep = getFileRep(f);
            repFlag = true;
        }
        else throw std::invalid_argument("Invalid file format.");
    }

    if (! (startFlag && endFlag && nameFlag && placeFlag && partFlag && repFlag))
        throw std::invalid_argument("Invalid file format.");
    
    Event event(start, end, name, place, participants, rep);
    storage.addEvent(event);
}

Time EventWrapper::getFileTime(std::ifstream &file) const {
    std::string buffer;
    char year[255];
    int mon, day, hour, min;

    getline(file, buffer);

    if (! sscanf(buffer.c_str(), " = %d.%d.%s %d:%d", &day, &mon, year, &hour, &min))
        throw std::invalid_argument("Invalid file format");

    return Time(year, mon, day, hour, min);
}

std::string EventWrapper::getFileString(std::ifstream &file) const {
    std::string name;

    if (! checkChar(file, '='))
        throw std::invalid_argument("Invalid file format");
    
    getline(file, name);

    return p.trimString(name);
}

std::vector<std::string> EventWrapper::getFilePart(std::ifstream &file) const {
    std::string part;
    
    if (! checkChar(file, '='))
        throw std::invalid_argument("Invalid file format");
    
    getline(file, part);

    return p.getVector(part);
}

int EventWrapper::getFileRep(std::ifstream &file) const {
    std::string rep = getFileString(file);

    for (int i = 0; i < 5; i++) {
        std::string repItem = repMenu[i];
        if (! strcasecmp(rep.c_str(), p.trimString(repItem).c_str()))
            return i;
    }

    return -1;
}

bool EventWrapper::checkChar(std::ifstream &file, char c) const {
    char in;
    if (! (file >> in))
        return false;
    if (in != c)
        return false;
    return true;
}

void EventWrapper::findName() const {
    std::vector<std::string> emptyVector;
    Event event(Time(), Time(), "", "", emptyVector, 0);
    Parser p;
    bool found = false;
    refresh();
    clear();
    move(0, 0);
    printw("Enter a name: ");
    std::string name = p.getString();
    storage.findName(name, found, event);
    clear();
    if (found)
        event.displayFull();
    else {
        printw("Name not found. Press a key to continue.");
        getch();
        clear();
    }
}   