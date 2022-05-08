#include <iostream>
#include <iomanip>

#include "displayCalendar.h"

const std::array<std::string, 12> DisplayCalendar::months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const std::array<std::string, 7> DisplayCalendar::days = {"sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void DisplayCalendar::displayHeader(const Time& time) const
{
    int year = time.time.tm_year + 1900, mon = time.time.tm_mon + 1;
    int spaces = (27 - months[mon].length() - lenYear(year)) / 2;
    if (spaces < 0)
        spaces = 0;

    std::cout << std::setfill(' ') << std::setw(spaces) << months[mon] << " " << year << std::endl;
}

void DisplayCalendar::displayDayNames() const
{
    for (auto day : days)
        std::cout << day << " ";
    std::cout << std::endl;
}

int DisplayCalendar::lenYear(int year) const
{
    int cnt;
    while (year)
    {
        cnt++;
        year /= 10;
    }

    return cnt;
}