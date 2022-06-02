#include <vector>
#include <memory>
#include <iostream>
#include <array>

#include "event.h"
//#include "stringParser.h"

class EventWrapper
{
public:
    void getEvent();
    Time getStart() const;
    Time getEnd() const;
    std::string getName() const;
    std::string getPlace() const;
    std::vector<std::string> getParticipants() const;
    int getRepetition() const;
    void insertEvent(const Time &);

private:
    std::vector<std::shared_ptr<Event>> eventsByStart;
    std::vector<std::shared_ptr<Event>> eventsByEnd;
    std::vector<std::shared_ptr<Event>> eventsByName;
    std::vector<std::shared_ptr<Event>> eventsByPlace;

    void insertStart(const Time &);
    void insertend(const Time &);
    void insertname(const Time &);
    void insertPlace(const Time &);
    void resetLine() const;
    void checkEventTime(const Time &, const Time &) const;
    void drawRepMenu(const int) const;
    void updatePos(const int, int &) const;

    static const std::array<std::string, 4> repMenu;
};