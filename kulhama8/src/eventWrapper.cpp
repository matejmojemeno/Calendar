#include "eventWrapper.h"

const std::array<std::string, 5> EventWrapper::repMenu = {" Never ", " Every day ", " Every week ", " Every two weeks ", " Every month "};

void EventWrapper::newEvent()
{
    clear();
    mvprintw(0, 0, "Enter an event:\n"); 

    try
    {
        Time start = getStart(), end = getEnd();
        std::string name = getName(), place = getPlace();
        std::vector<std::string> participants = getParticipants();
        int rep = getRepetition();
        callAddEvent(start, end, name, place, participants, rep);
    }
    catch (std::invalid_argument &ia)
    {
        showError(ia.what());
        return;
    }

}

void EventWrapper::callAddEvent(const Time &start, const Time &end, const std::string &name, const std::string &place, const std::vector<std::string> &participants, int rep)
{
    if (rep == DAILY) {
        DailyEvent event = DailyEvent(start, end, name, place, participants, rep); 
        storage.addEvent(event);
    }
    else if (rep == WEEKLY) {
        WeeklyEvent event = WeeklyEvent(start, end, name, place, participants, rep); 
        storage.addEvent(event);
    }
    else if (rep == TWOWEEKLY) {
        TwoWeeklyEvent event = TwoWeeklyEvent(start, end, name, place, participants, rep); 
        storage.addEvent(event);
    }
    else if (rep == MONTHLY) {
        MonthlyEvent event = MonthlyEvent(start, end, name, place, participants, rep); 
        storage.addEvent(event);
    }
    else 
    {
        OneTimeEvent event = OneTimeEvent(start, end, name, place, participants, rep); 
        storage.addEvent(event);
    }
}

Time EventWrapper::getStart() const
{
    printw("Start of the event: ");
    return p.parseDate();
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

void EventWrapper::resetLine() const
{
    int x, y;
    getyx(stdscr, x, y);
    move(x, 0);
    clrtoeol();
}

void EventWrapper::drawRepMenu(size_t pos) const
{
    for (size_t i = 0; i < repMenu.size(); i++)
    {
        if (i == pos)
            attron(COLOR_PAIR(1));
        printw(repMenu[i].c_str());
        attroff(COLOR_PAIR(1));
    }
}

int EventWrapper::getRepetition() const
{
    size_t pos = 0;
    drawRepMenu(0);

    int c = getch();
    while (c != 10)
    {
        refresh();
        updatePos(c, pos, repMenu.size());
        resetLine();
        drawRepMenu(pos);

        c = getch();
    }

    return pos;
}

void EventWrapper::updatePos(int c, size_t &pos, const size_t &menuSize) const
{
    if (c == KEY_LEFT)
        pos += menuSize - 1;
    else if (c == KEY_RIGHT)
        pos++;

    pos = pos % menuSize;
}

void EventWrapper::newFileEvent()
{
    clear();
    move(0, 0);
    std::string fileName = p.getString(), key, name, place;
    Time start, end;
    std::vector<std::string> participants;
    int rep = -1;
    bool startFlag = false, endFlag = false, nameFlag = false, placeFlag = false, partFlag = false, repFlag = false;

    std::ifstream f(fileName);

    if (!f.is_open() || !f.good()) {
        showError("Couldn't open file.");
        return;
    }

    while (f >> key)
    {
        if (!strcasecmp(key.c_str(), "start") && !startFlag)
        {
            start = getFileTime(f);
            startFlag = true;
        }
        else if (!strcasecmp(key.c_str(), "end") && !endFlag)
        {
            end = getFileTime(f);
            endFlag = true;
        }
        else if (!strcasecmp(key.c_str(), "name") && !nameFlag)
        {
            name = getFileString(f);
            nameFlag = true;
        }
        else if (!strcasecmp(key.c_str(), "place") && !placeFlag)
        {
            place = getFileString(f);
            placeFlag = true;
        }
        else if (!strcasecmp(key.c_str(), "participants") && !partFlag)
        {
            participants = getFilePart(f);
            partFlag = true;
        }
        else if (!strcasecmp(key.c_str(), "repetition") && !repFlag)
        {
            rep = getFileRep(f);
            repFlag = true;
        }
        else {
            showError("Wrong file format.");
            return;
        }
    }

    if (!(startFlag && endFlag && nameFlag && placeFlag && partFlag && repFlag)) {
        showError("Wrong file format.");
        return;
    }

    try
    {
        callAddEvent(start, end, name, place, participants, rep);
    }
    catch (std::invalid_argument &ia)
    {
        showError(ia.what());
    }
}

Time EventWrapper::getFileTime(std::ifstream &file) const
{
    std::string buffer;
    char year[255];
    int mon, day, hour, min;

    getline(file, buffer);

    if (!sscanf(buffer.c_str(), " = %d.%d.%s %d:%d", &day, &mon, year, &hour, &min))
        throw std::invalid_argument("Invalid file format");

    return Time(year, mon, day, hour, min);
}

std::string EventWrapper::getFileString(std::ifstream &file) const
{
    std::string name;

    if (!checkChar(file, '='))
        throw std::invalid_argument("Invalid file format");

    getline(file, name);

    return p.trimString(name);
}

std::vector<std::string> EventWrapper::getFilePart(std::ifstream &file) const
{
    std::string part;

    if (!checkChar(file, '='))
        throw std::invalid_argument("Invalid file format");

    getline(file, part);

    return p.getVector(part);
}

int EventWrapper::getFileRep(std::ifstream &file) const
{
    std::string rep = getFileString(file);

    for (int i = 0; i < 5; i++)
    {
        std::string repItem = repMenu[i];
        if (!strcasecmp(rep.c_str(), p.trimString(repItem).c_str()))
            return i;
    }

    return -1;
}

bool EventWrapper::checkChar(std::ifstream &file, char c) const
{
    char in;
    if (!(file >> in))
        return false;
    if (in != c)
        return false;
    return true;
}

void EventWrapper::showError(const char * error) const
{
    clear();
    mvprintw(0, 0, "%s\nPress a key to continue.", error);
    getch();
}

std::vector<std::shared_ptr<Event>> EventWrapper::eventsByName() const
{
    clear();
    std::string name = getName();
    return storage.findName(name);
}

std::vector<std::shared_ptr<Event>> EventWrapper::eventsByPlace() const
{
    clear();
    std::string place = getPlace();
    return storage.findPlace(place);
}

void EventWrapper::manageEvents(std::vector<std::shared_ptr<Event>> &events)
{
    size_t pos = 0, c = 0;
    if (events.empty()) {
        showError("No events found.");
        return;
    }

    while (c != 4)
    {
        events[pos]->displayFull();
        int c = getch();
        clear();
        updatePos(c, pos, events.size());
        if (callFunc(events[pos], c)) 
            return;
    }
}

bool EventWrapper::callFunc(std::shared_ptr<Event> event, int c)
{
    if (c == '1')
    {
        Time time = getStart();
        storage.moveEvent(event, time);
    }
    else if (c == '2') 
        storage.removeEvent(event);
    else if (c == '3')
        event->exportEvent();
    else if (c == 4)
        return true;
    else
        return false;

    return true;
}