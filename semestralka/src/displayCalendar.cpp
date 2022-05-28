#include "displayCalendar.h"

const std::array<const char *, 12> DisplayCalendar::months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const std::array<const char *, 7> DisplayCalendar::days = {"sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void DisplayCalendar::displayHeader(const Time& time) const
{
    mvprintw(10, 0, months[time.m_mon - 1]);
    mvprintw(11 + strlen(months[time.m_mon - 1]), 0, "%d", time.m_year);
}

void DisplayCalendar::displayDayNames() const
{
    for (int i = 0; i < 7; i++)
        mvprintw(1, i*4 + 3, days[i]);
}

// int DisplayCalendar::lenYear(int year) const
// {
//     int cnt;
//     while (year)
//     {
//         cnt++;
//         year /= 10;
//     }

//     return cnt;
// }

void DisplayCalendar::display(const Time &time) const
{   
    displayHeader(time);
    displayDayNames();
    displayDays(time);
}