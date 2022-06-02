#include <vector>
#include <string>
#include "stringParser.h"

class Event
{
public:
    Event(const Time, const Time, std::string, std::string, std::vector<std::string>);

    //void displaySmall() const;
    void displaySmall(int, bool) const;
    void displayFull(int) const;

private:
    Time start, end;
    std::vector<std::string> participants;
    std::string name, place;
};