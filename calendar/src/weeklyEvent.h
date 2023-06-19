#include "dailyEvent.h"

class WeeklyEvent : public Event {
public:
    /**
     * @brief Construct a new Weekly Event object
     */
    WeeklyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    /**
     * @brief Construct a new Weekly Event object
     * copy constructor
     */
    WeeklyEvent(const Event &);
    /**
     * @brief 
     * checks if event happens on given day
     * @return true 
     * @return false 
     */
    bool isSameDay(const Time &) const override;
};