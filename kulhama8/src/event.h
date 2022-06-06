#include <vector>
#include <string>
#include <fstream>
#include "stringParser.h"

#define NEVER 0
#define DAILY 1
#define WEEKLY 2
#define TWOWEEKLY 3
#define MONTHLY 4

class Event
{
public:
    /**
     * @brief Construct a new Event object
     * creates dummy event instance, needs to be changed before being used
     */
    Event();
    /**
     * @brief Construct a new Event object
     * creates a new instance of event
     */
    Event(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);

    /**
     * @brief 
     * displays just name and starting time of event
     */
    void displaySmall(int, bool) const;
    /**
     * @brief 
     * displays everything about event
     */
    int displayFull() const;
    /**
     * @brief 
     * moves event to another day
     * @return Event 
     */
    Event operator+(int);

    /**
     * @brief 
     * prints event into file
     */
    void exportEvent() const;

    Time start, end;
    std::vector<std::string> participants;
    std::string name, place;
    int rep;
private:
    std::string getRep(int) const;
};