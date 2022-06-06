#include <tuple>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

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
     * constructs date based on given arguments
     */
    Time(int, int, int, int, int);
    /**
     * @brief Construct a new Time object
     * constructs Time while checking for integer overflow
     */
    Time(std::string, int, int, int, int);
    /**
     * @brief Construct a new Time object
     * copy constructor
     */
    Time(const Time &);
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
    bool isLeap(int) const;
    /**
     * @brief 
     * return number of days of current year
     * @return int 
     */
    int monthDays(int, int) const;
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
    int dayNumber(int, int, int) const;
    /**
     * @brief 
     * counts leap years in an interval
     * @return int 
     */
    int countLeapYears(int) const;
    /**
     * @brief 
     * returns number of days from day 0 to current date
     * @return long long 
     */
    long long toDays() const;
    /**
     * @brief 
     * turns number of days back to date
     * @param long 
     */
    void toDate(long long);
    /**
     * @brief 
     * return copy of object increased by n days
     * @return Time 
     */
    Time operator+(int) const;
    /**
     * @brief 
     * return copy of object decreased by n days
     * @return Time 
     */
    Time operator-(int) const;
    /**
     * @brief 
     * returns number of minutes between two dates
     * @return long long 
     */
    long long operator-(const Time &) const;
    /**
     * @brief 
     * checks if week is odd or even
     * @return true 
     * @return false 
     */
    bool isEvenWeek() const;
    /**
     * @brief 
     * adjusts time if it is wrong
     */
    void adjustTime();

    int m_year, m_mon, m_day, m_hour, m_min;

private:
    /**
     * @brief Get the Year object
     * functions called by
     * @param long 
     */
    void getYear(long long&);
    void adjust(long long&);
    void getMon(long long&);
    void zeroTime();
};