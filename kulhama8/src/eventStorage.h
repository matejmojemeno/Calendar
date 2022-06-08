#include <memory>
#include <algorithm>
#include "event.h"

#define ONE_DAY 1
#define DAYS_IN_WEEK 7
#define DAYS_IN_TWOWEEKS 14

class EventStorage
{
public:
    /**
     * @brief 
     * adds new event
     */
    void addEvent(const Event &);
    /**
     * @brief 
     * returns all events happening on given day
     * @return std::vector<Event> 
     */
    std::vector<Event> dayEvents(const Time &) const;
    /**
     * @brief 
     * finds event with given name
     */
    void findName(const std::string &, bool &, Event &) const;
    /**
     * @brief 
     * removes event with given name if exists
     */
    void removeEvent(const std::string &);
    /**
     * @brief 
     * moves event to a new date
     */
    void moveEvent(const Event &, const Time &);
    /**
     * @brief 
     * vectors to store all events
     */
    std::vector<Event> allEvents;
    std::vector<Event> eventsByStart;
    std::vector<Event> eventsByEnd;
    std::vector<Event> dailyEvents;
    std::vector<Event> weeklyEvents;
    std::vector<Event> twoWeeklyEvents;
    std::vector<Event> monthlyEvents;

private:
    /**
     * @brief 
     * check if event can be added
     * @return true 
     * @return false 
     */
    bool checkEvent(const Event &) const;
    /**
     * @brief 
     * check if date of event doesnt collide with other events
     * @return true 
     * @return false 
     */
    bool checkDate(const Event &) const;
    /**
     * @brief 
     * check if name of event doesnt collide with other events
     * @return true 
     * @return false 
     */
    bool checkName(const std::string &) const;
    /**
     * @brief 
     * finds new starting date to event
     * @return Time 
     */
    Time findNewDate(const Event &) const;
    /**
     * @brief 
     * removes event from vector without repetition
     */
    void removeNoRep(const std::string &);
    /**
     * @brief 
     * removes event from repetition vectors
     */
    void removeRep(const std::string &, std::vector<Event> &);
    /**
     * @brief 
     * requests a new name for event
     */
    void newName(const Event &);
    /**
     * @brief 
     * iterates all events to check dates
     * @return true 
     * @return false 
     */
    bool iterateEvents(const Event &, const std::vector<Event> &) const;
    /**
     * @brief 
     * check if two events collide
     * @return true 
     * @return false 
     */
    bool intersectEvent(const Event &, const Event &) const;
    /**
     * @brief 
     * inserts event
     */
    void insert(const Event &);
    /**
     * @brief 
     * inserts event while sorting based on start of event
     */
    void insertStart(const Event &);
    /**
     * @brief 
     * inserts event while sorting based on end of event
     */
    void insertEnd(const Event &);
    /**
     * @brief 
     * inserts repeated event
     */
    void insertRepeated(const Event &);
    /**
     * @brief 
     * functions called by dayEvents
     */
    void sameDay(std::vector<Event> &, const Time &) const;
    void sameDayReps(std::vector<Event> &, const Time &) const;
    void sameWeekReps(std::vector<Event> &, const Time &) const;
    void sameTwoWeekReps(std::vector<Event> &, const Time &) const;
    void sameMonthReps(std::vector<Event> &, const Time &) const;
};