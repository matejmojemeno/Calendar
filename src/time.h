#include <tuple>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include "constants.h"

class Time
{
public:
    /**
     * @brief Construct a new Time object
     * construct current date
     */
    Time();
    /**
     * @brief Construct a new Time object
     * creates Time object with current date and given time
     */
    Time(long long, long long);
    /**
     * @brief Construct a new Time object
     * constructs date based on given arguments
     */
    Time(long long, long long, long long, long long, long long);
    /**
     * @brief Construct a new Time object
     * constructs Time while checking for integer overflow
     */
    Time(std::string, long long, long long, long long, long long);
    /**
     * @brief
     * operators to compare two Times
     * @return true
     * @return false
     */
    bool operator<(const Time &) const;
    bool operator<=(const Time &) const;
    bool operator==(const Time &) const;
    /**
     * @brief
     * checks if year is leap
     * @return true
     * @return false
     */
    bool isLeap(long long) const;
    /**
     * @brief
     * return number of days of current year
     * @return int
     */
    int monthDays(long long, long long) const;
    /**
     * @brief
     * return number of days of given month in a given year
     * @return int
     */
    int monthDays() const;
    /**
     * @brief
     * checks validity of date
     * @return true
     * @return false
     */
    bool checkDate() const;
    /**
     * @brief
     * returns order of current day in week
     * @return int
     */
    int dayNumber() const;
    /**
     * @brief
     * returns order of given day in week
     * @return int
     */
    int dayNumber(long long, long long, long long) const;
    /**
     * @brief
     * counts leap years in an interval
     * @return int
     */
    int countLeapYears(long long) const;
    /**
     * @brief
     * returns number of days from day 0 to current date
     * @return long long
     */
    long long toMinutes() const;
    /**
     * @brief
     * turns number of days back to date
     * @param long
     */
    void toDate(long long);
    /**
     * @brief
     * return copy of object increased by n minutes
     * @param long
     * @return Time
     */
    Time operator+(long long) const;
    /**
     * @brief
     * returns number of minutes between two dates
     * @return long long
     */
    Time operator-(long long amount) const;
    long long operator-(const Time &) const;
    /**
     * @brief
     * checks if week is odd or even
     * @return true
     * @return false
     */
    bool isEvenWeek() const;

    long long m_year, m_mon, m_day, m_hour, m_min;

private:
    /**
     * @brief Get the Year object
     * functions called by toDate
     * @param long
     */
    void getYear(long long &);
    void getMon(long long &);
    void getDays(long long &);
    void getHours(long long &);
    /**
     * @brief 
     * checks if remainder isnt whole year
     */
    void adjustMinutes(long long &);
    /**
     * @brief 
     * checks if time is positive, sets to day 1 if not
     */
    void fixNegativeTime();
};