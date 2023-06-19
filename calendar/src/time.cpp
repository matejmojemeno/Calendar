#include "time.h"

Time::Time()
{
    std::time_t t = std::time(0);
    struct tm *now = localtime(&t);

    m_year = (long long)now->tm_year + 1900;
    m_mon = (long long)now->tm_mon + 1;
    m_day = (long long)now->tm_mday;
    m_hour = m_min = 0;
}

Time::Time(long long hour, long long min)
{
    Time();
    m_hour = hour;
    m_min = min;
}

Time::Time(long long year, long long mon, long long day, long long hour, long long min)
{
    m_year = year;
    m_mon = mon;
    m_day = day;
    m_hour = hour;
    m_min = min;

    if (!checkDate())
        throw std::invalid_argument("Invalid date or format.");
}

Time::Time(std::string year, long long mon, long long day, long long hour, long long min)
{
    try
    {
        m_year = stoll(year);
    }
    catch (...)
    {
        throw std::invalid_argument("Invalid date or format.");
    }
    m_mon = mon;
    m_day = day;
    m_hour = hour;
    m_min = min;

    if (!checkDate())
        throw std::invalid_argument("Invalid date or format.");
}

bool Time::operator<(const Time &rs) const
{
    return std::tie(m_year, m_mon, m_day, m_hour, m_min) < std::tie(rs.m_year, rs.m_mon, rs.m_day, rs.m_hour, rs.m_min);
}

bool Time::operator<=(const Time &rs) const
{
    return std::tie(m_year, m_mon, m_day, m_hour, m_min) <= std::tie(rs.m_year, rs.m_mon, rs.m_day, rs.m_hour, rs.m_min);
}

bool Time::operator==(const Time &rs) const
{
    return std::tie(m_year, m_mon, m_day, m_hour, m_min) == std::tie(rs.m_year, rs.m_mon, rs.m_day, rs.m_hour, rs.m_min);
}

bool Time::isLeap(long long year) const
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

int Time::monthDays(long long year, long long mon) const
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
    if (m_year > MAX_YEAR || m_mon > 12 || m_day > monthDays() || m_hour > 23 || m_min > 59)
        return false;
    return true;
}

int Time::dayNumber() const
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int year = m_year - (m_mon < 3);
    return (year + year / 4 - year / 100 + year / 400 - year / 4000 + t[m_mon - 1] + m_day) % 7;
}

int Time::dayNumber(long long year, long long mon, long long day) const
{
    static long long t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= mon < 3;
    return (year + year / 4 - year / 100 + year / 400 - year / 4000 + t[mon - 1] + day) % 7;
}

int Time::countLeapYears(long long year) const
{
    return (year / 4 - year / 100 + year / 400 - year / 4000);
}

long long Time::toMinutes() const
{
    long long minutes = m_year * YEAR + countLeapYears(m_year - 1) * DAY;

    for (int i = 1; i < m_mon; i++)
        minutes += monthDays(m_year, i) * DAY;

    return minutes + m_day * DAY + m_hour * HOUR + m_min;
}

void Time::toDate(long long minutes)
{
    m_year = m_hour = m_min = 0;
    m_mon = m_day = 1;

    getYear(minutes);
    adjustMinutes(minutes);
    getMon(minutes);
    getDays(minutes);
    getHours(minutes);
    m_min = minutes;
}

void Time::getYear(long long &minutes)
{
    while ((minutes - toMinutes()) / (LEAP_YEAR_DAYS * DAY))
    {
        m_year += (minutes - toMinutes()) / (LEAP_YEAR_DAYS * DAY);
    }
    minutes -= toMinutes();
}

void Time::getMon(long long &minutes)
{
    while (minutes >= monthDays() * DAY)
    {
        minutes -= monthDays() * DAY;
        m_mon++;
    }
}

void Time::getDays(long long &minutes)
{
    m_day += minutes / DAY;
    minutes %= DAY;
}

void Time::getHours(long long &minutes)
{
    m_hour = minutes / HOUR;
    minutes %= HOUR;
}

void Time::adjustMinutes(long long &minutes)
{
    if (minutes >= YEAR && !isLeap(m_year))
    {
        m_year++;
        minutes -= YEAR;
    }
}

Time Time::operator+(long long amount) const
{
    Time tmp;

    if (!amount)
        return *this;

    tmp.toDate(toMinutes() + amount);
    tmp.fixNegativeTime();

    return tmp;
}

Time Time::operator-(long long amount) const
{
    Time tmp;

    if (!amount)
        return *this;

    tmp.toDate(toMinutes() - amount);
    tmp.fixNegativeTime();

    return tmp;
}

long long Time::operator-(const Time &rs) const
{
    return toMinutes() - rs.toMinutes();
}

void Time::fixNegativeTime()
{
    if (m_day < 1 || m_hour < 0 || m_min < 0)
    {
        m_day = 1;
        m_hour = m_min = 0;
    }
}

bool Time::isEvenWeek() const
{
    return !((toMinutes() % (2 * WEEK)) / WEEK);
}

// int main ()
// {
//     Time time;
//     std::cout << time.toMinutes() << std::endl;
//     std::cout << time.m_year << " " << time.m_mon << " " << time.m_day << " " << time.m_hour << " " << time.m_min << std::endl;
//     time = time + 100;
//     std::cout << time.m_year << " " << time.m_mon << " " << time.m_day << " " << time.m_hour << " " << time.m_min << std::endl;

//     std::cout << time.dayNumber() << std::endl;
//     time = time + DAY;
//     std::cout << time.dayNumber() << std::endl;

//     return 0;
// }