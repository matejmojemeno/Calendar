#include <tuple>
#include <ctime>
#include <stdexcept>

class Time
{
public:
    Time();
    Time(int, int, int, int, int);
    bool operator<(const Time &) const;
    bool operator==(const Time &) const;
    bool isLeap(int) const;
    int monthDays(int, int) const;
    int monthDays() const;
    bool checkDate() const;
    int dayNumber() const;
    int dayNumber(int, int, int) const;
    int countLeapYears(int) const;
    long long toDays() const;
    void toDate(long long);
    Time &operator+(const int);
    Time &operator-(const int);

    int m_year, m_mon, m_day, m_hour, m_min;

private:
    void getYear(long long&);
    void adjust(long long&);
    void getMon(long long&);
    void zeroTime();
};