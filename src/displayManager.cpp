#include "displayManager.h"

const std::map<std::string, std::shared_ptr<Display>> DisplayManager::displays =
    {
        {"monthly", std::make_shared<DisplayMonth>()},
        {"weekly", std::make_shared<DisplayWeek>()},
        {"daily", std::make_shared<DisplayDay>()}};

void DisplayManager::display(const EventStorage &storage) const
{
    std::string displayType = "monthly";
    int c = 0;
    Time time;
    while (c != BACK)
    {
        changeTime(time, c, displayType);
        changeDisplay(displayType, c, time);
        displays.at(displayType)->display(time, storage);
        c = getch();
    }
}

void DisplayManager::changeTime(Time &time, int c, const std::string &displayType) const
{
    if (c == KEY_LEFT)
        time = time - DAY;
    else if (c == KEY_RIGHT)
        time = time + DAY;
    else if (c == KEY_UP && displayType == "monthly")
        time = time - WEEK;
    else if (c == KEY_DOWN && displayType == "monthly")
        time = time + WEEK;
}

void DisplayManager::changeDisplay(std::string &displayType, int c, Time &time) const
{
    if (c == '1' && displayType != "monthly")
    {
        displayType = "monthly";
        time = Time();
    }
    else if (c == '2' && displayType != "weekly")
    {
        displayType = "weekly";
        time = Time();
    }
    else if (c == '3' && displayType != "daily")
    {
        displayType = "daily";
        time = Time();
    }
}