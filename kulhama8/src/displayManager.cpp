#include "displayManager.h"

const std::map<std::string, std::shared_ptr<Display>> DisplayManager::displays = 
{
    {"monthly", std::make_shared<DisplayMonth>()},
    {"weekly", std::make_shared<DisplayWeek>()},
    {"daily", std::make_shared<DisplayDay>()}
};

void DisplayManager::display(const EventStorage &storage) const
{
    std::string displayType = "monthly";
    int c = 0;
    while(c != BACK)
    {
        Time time;
        displays.at(displayType)->controlDisplay(time, storage);
    }
}