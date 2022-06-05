#include <vector>
#include <string>
#include "stringParser.h"

#define NEVER 0
#define DAILY 1
#define WEEKLY 2
#define TWOWEEKLY 3
#define MONTHLY 4

class Event
{
public:
    Event(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);

    void displaySmall(int, bool) const;
    void displayFull() const;
    Event operator+(int);

    Time start, end;
    std::vector<std::string> participants;
    std::string name, place;
    int rep;
};