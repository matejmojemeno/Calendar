#include "twoWeeklyEvent.h"

class MonthlyEvent : public Event {
public:  
    /**
     * @brief Construct a new Monthly Event object
     */
    MonthlyEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    /**
     * @brief Construct a new Monthly Event object
     * copy constructor
     */
    MonthlyEvent(const Event &);
    /**
     * @brief 
     * checks if event happens on given day
     * @return true 
     * @return false 
     */
    bool isSameDay(const Time &) const override;
};