#include "weeklyEvent.h"

class TwoWeeklyEvent : public Event
{
public:
    /**
     * @brief Construct a new Two Weekly Event object
     */
    TwoWeeklyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    /**
     * @brief Construct a new Two Weekly Event object
     * copy constructor
     */
    TwoWeeklyEvent(const Event &);
    /**
     * @brief 
     * checks if event happens on given day
     * @return true 
     * @return false 
     */
    bool isSameDay(const Time &) const override;
};