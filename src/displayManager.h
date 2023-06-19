#include <map>

#include "displayMonth.h"

class DisplayManager
{
public:
    /**
     * @brief 
     * displays a calendar :)
     */
    void display(const EventStorage &) const;
private:
    /**
     * @brief 
     * changes time if appropriate key is pressed
     * @param c 
     */
    void changeTime(Time &, int c, const std::string &) const;
    /**
     * @brief 
     * changes display type if appropriate key is pressed
     * @param c 
     */
    void changeDisplay(std::string &, int c, Time &) const;
    static const std::map<std::string, std::shared_ptr<Display>> displays;
};