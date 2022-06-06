#include <iostream>
#include <array>
#include <algorithm>

#include "eventStorage.h"

class EventWrapper
{
public:
    void getEvent();
    void getFileEvent();
    void manageEvent();
    void doOperation(int op, const Event &, const std::string &);

    Time getStart() const;
    Time getEnd() const;
    std::string getName() const;
    std::string getPlace() const;
    std::vector<std::string> getParticipants() const;
    int getRepetition() const;

    EventStorage storage;
private:
    void resetLine() const;
    void checkEventTime(const Time &, const Time &) const;
    void drawRepMenu(const int) const;
    void updatePos(const int, int &) const;
    bool checkChar(std::ifstream &, char) const;
    Time getFileTime(std::ifstream &) const;
    std::string getFileString(std::ifstream &) const;
    std::vector<std::string> getFilePart(std::ifstream &) const;
    int getFileRep(std::ifstream &) const;

    Parser p;
    static const std::array<std::string, 5> repMenu;
};