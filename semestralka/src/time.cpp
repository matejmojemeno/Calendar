#include "time.h"

Time::Time()
{
    time_t rawTime;
    struct tm *tmp;
    tmp = std::localtime(&rawTime);
    time = *tmp;
    time.tm_sec = 0;
    time.tm_isdst = 0;
}

Time::Time(int year, int mon, int day, int hour, int min)
{
    struct tm tmp = {0, min, hour, day, mon - 1, year - 1900, 0, 0, 0};
    checkDate(tmp);
    mktime(&tmp);
    time = tmp;
}

bool Time::operator<(const Time &rs) const
{
    return less(time, rs.time);
}

bool Time::operator==(const Time &rs) const
{
    return !(*this < rs || *this < rs);
}

bool Time::less(const struct tm &ls, const struct tm &rs) const
{
    return std::tie(ls.tm_year, ls.tm_mon, ls.tm_mday, ls.tm_hour, ls.tm_min) < std::tie(rs.tm_year, rs.tm_mon, rs.tm_mday, rs.tm_hour, rs.tm_min);
}

bool Time::equal(const struct tm &ls, const struct tm &rs) const
{
    return !(less(ls, rs) || less(ls, rs));
}

bool Time::isLeap(int year) const
{
    return year % 4000 && (!(year % 400) || (year % 100 && !(year % 4)));
}

//int Time::monthDays(int year, int mon) const
//{
//    if (mon == 2)
//        return 28 + isLeap(year);
//    if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
//        return 30;
//    return 31;
//}

int Time::monthDays() const {
    int year = time.tm_year + 1900, mon = time.tm_mon + 1;
    if (mon == 2)
        return 28 + isLeap(year);
    if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
        return 30;
    return 31;
}

bool Time::checkDate(struct tm time) const
{
    struct tm copy = time;
    time_t check = mktime(&time);
    if (!(equal(time, copy)) || check == -1)
        return false;
    return true;
}

int Time::dayNumber() const
{
    int year = time.tm_year + 1900, month = time.tm_mon + 1, day = time.tm_mday;
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}