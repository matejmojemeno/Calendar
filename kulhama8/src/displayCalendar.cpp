#include "displayCalendar.h"

const std::array<const char *, 12> DisplayCalendar::months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const std::array<const char *, 7> DisplayCalendar::days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const std::array<const char *, 7> DisplayCalendar::fullDays = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

DisplayCalendar::~DisplayCalendar() = default;

void DisplayCalendar::displayHeader(const Time& time) const
{
    mvprintw(0, 10, months[time.m_mon - 1]);
    mvprintw(0, 11 + strlen(months[time.m_mon - 1]), "%d", time.m_year);
}

void DisplayCalendar::displayDayNames() const
{
    for (int i = 0; i < 7; i++)
        mvprintw(1, i*4 + 3, days[i]);
}

void DisplayCalendar::display(const Time &time) const
{   
    clear();
    displayHeader(time);
    displayDayNames();
    displayDays(time);
}