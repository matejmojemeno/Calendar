#include "oneTimeEvent.h"

class DailyEvent : public Event 
{
public:
    /**
     * @brief Construct a new Daily Event object
     */
    DailyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    /**
     * @brief Construct a new Daily Event object
     * copy constructor
     */
    DailyEvent(const Event &);
    /**
     * @brief 
     * finds if event happens on given day
     * @return true 
     * @return false 
     */
    bool isSameDay(const Time &) const override; 
};