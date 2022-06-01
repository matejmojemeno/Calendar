#include <vector>
#include <string>
#include "time.h"

class Event
{
public:
    Event(const Time &, const Time &, std::vector<std::string>, std::string);
    
private:
    Time start, end;
    std::vector<std::string> participants;
    std::string place;
};