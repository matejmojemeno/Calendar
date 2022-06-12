#include <memory>
#include <algorithm>
#include "monthlyEvent.h"

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
    void addEvent(Event &);
    /**
     * @brief 
     * returns all events happening on given day
     * @return std::vector<Event> 
     */
    std::vector<std::shared_ptr<Event>> dayEvents(const Time &) const;
    /**
     * @brief 
     * finds all events with given name
     */
    std::vector<std::shared_ptr<Event>> findName(const std::string &) const;
    /**
     * @brief 
     * finds all events with given name
     */
    std::vector<std::shared_ptr<Event>> findPlace(const std::string &) const;
    /**
     * @brief 
     * removes event with given name if exists
     */
    void removeEvent(const std::shared_ptr<Event>);
    /**
     * @brief 
     * moves event to a new date
     */
    bool moveEvent(std::shared_ptr<Event>, const Time &);
    /**
     * @brief 
     * vectors to store all events
     */
    std::vector<std::shared_ptr<Event>> allEvents;
    std::vector<std::shared_ptr<OneTimeEvent>> eventsByStart;
    std::vector<std::shared_ptr<OneTimeEvent>> eventsByEnd;

private:
    /**
     * @brief 
     * adds one time event to the storage
     */
    void addOneTime(const OneTimeEvent &);
    /**
     * @brief 
     * adds repeated event to the storage
     */
    void addRep(const Event &);
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
    bool checkDate(const OneTimeEvent &) const;
    /**
     * @brief 
     * finds new starting date to event
     * @return Time 
     */
    Time findNewStart(const OneTimeEvent &) const;
    /**
     * @brief 
     * finds the next closest start after some date
     * @return Time 
     */
    Time nextStart(const Time &) const;
    /**
     * @brief 
     * asks user if he wants to move event
     * @return true 
     * @return false 
     */
    bool wantNewDate() const;
    /**
     * @brief 
     * removes event from vector of all events
     */
    void removeAll(const std::shared_ptr<Event>);
    /**
     * @brief 
     * removes event from sorted vectors
     */
    void removeByStart(const Event &);
    void removeByEnd(const Event &);
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
    void insertNoRep(const Event &);
    /**
     * @brief 
     * inserts event while sorting based on start of event
     */
    void insertByStart(const std::shared_ptr<OneTimeEvent> &);
    /**
     * @brief 
     * inserts event while sorting based on end of event
     */
    void insertByEnd(const std::shared_ptr<OneTimeEvent> &);
};