#include "event.h"

class OneTimeEvent : public Event 
{
public:
    /**
     * @brief Construct a new One Time Event object
     */
    OneTimeEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    /**
     * @brief Construct a new One Time Event object
     * copy constructor
     */
    OneTimeEvent(const Event &);
    /**
     * @brief 
     * checks if event happens on given day
     * @return true 
     * @return false 
     */
    bool isSameDay(const Time &) const override;
    /**
     * @brief 
     * checks if two events intersect
     * @return true 
     * @return false 
     */
    bool intersectEvent(const Event &) const;
    /**
     * @brief 
     * ask user if he wants to move the event
     * @return true 
     * @return false 
     */
    bool wantToMove(const Time &) const;
    /**
     * @brief 
     * print the move request
     */
    void printRequest(const Time &) const;
};