#include "time.h"

Time::Time()
{
    std::time_t t = std::time(0);
    struct tm *now = localtime(&t);

    m_year = now->tm_year + 1900;
    m_mon = now->tm_mon + 1;
    m_day = now->tm_mday;
    m_hour = m_min = 0;
}

Time::Time(int year, int mon, int day, int hour, int min)
{
    m_year = year;
    m_mon = mon;
    m_day = day;
    m_hour = hour;
    m_min = min;

    if (! checkDate())
        throw std::invalid_argument("Invalid date or format");
}

bool Time::operator<(const Time &rs) const
{
    return std::tie(m_year, m_mon, m_day, m_hour, m_min) < std::tie(rs.m_year, rs.m_mon, rs.m_day, rs.m_hour, rs.m_min);
}

bool Time::operator==(const Time &rs) const
{
    return !(*this < rs || *this < rs);
}

bool Time::isLeap(int year) const
{
    return year % 4000 && (!(year % 400) || (year % 100 && !(year % 4)));
}

int Time::monthDays() const
{
    if (m_mon == 2)
        return 28 + isLeap(m_year);
    if (m_mon == 4 || m_mon == 6 || m_mon == 9 || m_mon == 11)
        return 30;
    return 31;
}

int Time::monthDays(int year, int mon) const
{
    if (mon == 2)
        return 28 + isLeap(year);
    if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
        return 30;
    return 31;
}

bool Time::checkDate() const
{
    if (m_year < 0 || m_mon < 1 || m_day < 1 || m_hour < 0 || m_min < 0)
        return false;
    if (m_mon > 12 || m_day > monthDays() || m_hour > 23 || m_min > 59)
        return false;
    return true;
}

int Time::dayNumber() const
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int year = m_year - (m_mon < 3);
    return (year + year / 4 - year / 100 + year / 400 - year / 4000 + t[m_mon - 1] + m_day) % 7;
}

int Time::dayNumber(int year, int mon, int day) const
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= mon < 3;
    return (year + year / 4 - year / 100 + year / 400 - year / 4000 + t[mon - 1] + day) % 7;
}

int Time::countLeapYears(int year) const
{
    return (year / 4 - year / 100 + year / 400 - year / 4000);
}

long long Time::toDays() const
{
    long long days = m_year * 365 + countLeapYears(m_year - 1);

    for (int i = 1; i < m_mon; i++)
        days += monthDays(m_year, i);

    return days + m_day;
}

void Time::toDate(long long days)
{
    m_year = 0;
    m_mon = m_day = 1;

    getYear(days);
    adjust(days);
    getMon(days);
    m_day += days;
}

void Time::getYear(long long &days) {
    while ((days - toDays()) / 366) {
        m_year += (days - toDays()) / 366;
    }
    days -= toDays();
}

void Time::adjust(long long &days) {
    if (days == 365 && !isLeap(m_year)) {
        m_year++;
        days = 0;
    }
}

void Time::getMon (long long &days) {
    while (days >= monthDays()) {
        days -= monthDays();
        m_mon++;
    }
}

Time &Time::operator+(int amount) {
    if (! amount)
        return *this;
    toDate(toDays() + amount);
    zeroTime();
    return *this;
}

Time &Time::operator-(int amount) {
    if (! amount)
        return *this;
    toDate(toDays() - amount);
    zeroTime();
    return *this;
}

void Time::zeroTime() {
    if (m_day < 1)
        m_day = 1;
}