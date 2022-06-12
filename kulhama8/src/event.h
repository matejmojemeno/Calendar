#include <vector>
#include <string>
#include <fstream>
#include <memory>
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
     * @brief Construct a new Event object
     * event copy constructor
     */
    Event(const Event &);
    /**
     * @brief Destroy the Event object
     * virtual destructor of base class
     */
    virtual ~Event();
    /**
     * @brief 
     * checks if all atributes of events are same
     * @return true 
     * @return false 
     */
    bool operator==(const Event &) const;
    /**
     * @brief 
     * moves event to a new start
     * adjusts end accordingly
     */
    void move(const Time &);
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
     * checks if event happens on given day
     * @return true 
     * @return false 
     */
    virtual bool isSameDay(const Time &) const = 0;
    /**
     * @brief 
     * prints event into file
     */
    void exportEvent() const;

    Time start, end;
    std::vector<std::string> participants;
    std::string name, place;
    int rep;
};