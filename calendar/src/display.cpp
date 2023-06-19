#include "display.h"

const std::vector<const char *> Display::months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const std::vector<const char *> Display::days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const std::vector<const char *> Display::fullDays = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Display::~Display() = default;

void Display::displayHeader(const Time& time) const
{
    mvprintw(0, 10, months[time.m_mon - 1]);
    mvprintw(0, 11 + strlen(months[time.m_mon - 1]), "%d", time.m_year);
}

void Display::displayDayNames() const
{
    for (int i = 0; i < 7; i++)
        mvprintw(1, i*DAY_SIZE + OFFSET, days[i]);
}

void Display::displayEvents(const Time &time, const EventStorage &events) const
{
    std::vector<std::shared_ptr<Event>> eventsList = events.dayEvents(time);

    for (size_t i = 0; i < eventsList.size(); i++)
        eventsList[i]->displaySmall(i + OFFSET);
}