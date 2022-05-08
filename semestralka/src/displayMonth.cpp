#include <iostream>
#include <iomanip>

#include "displayMonth.h"

void DisplayMonth::displayDays(const Time &time) const
{
    int dayOfWeek = time.dayNumber(), monthDays = time.monthDays();

    std::cout << std::setfill(' ') << std::setw(dayOfWeek*4);

    for (int i = 1; i < monthDays; i++) {
        std::cout << i << " ";

        if (++dayOfWeek > 6) {
            dayOfWeek = 0;
            std::cout << std::endl;
        }
    }

    if (dayOfWeek)
        std::cout << std::endl; 
}