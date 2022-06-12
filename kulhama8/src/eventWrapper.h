#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

#include "eventStorage.h"

class EventWrapper
{
public:
    void newEvent();
    void newFileEvent();
    void manageEvents(std::vector<std::shared_ptr<Event>> &);
    std::vector<std::shared_ptr<Event>> eventsByName() const;
    std::vector<std::shared_ptr<Event>> eventsByPlace() const;

    EventStorage storage;

private:
    void callAddEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    Time getStart() const;
    Time getEnd() const;
    std::string getName() const;
    std::string getPlace() const;
    std::vector<std::string> getParticipants() const;
    int getRepetition() const;
    void resetLine() const;
    void drawRepMenu(size_t) const;
    void updatePos(int, size_t &, const size_t &) const;
    bool checkChar(std::ifstream &, char) const;
    Time getFileTime(std::ifstream &) const;
    std::string getFileString(std::ifstream &) const;
    std::vector<std::string> getFilePart(std::ifstream &) const;
    int getFileRep(std::ifstream &) const;
    bool callFunc(std::shared_ptr<Event>, int);
    void showError(std::invalid_argument &) const;

    Parser p;
    static const std::array<std::string, 5> repMenu;
};