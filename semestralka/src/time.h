#include <tuple>
#include <ctime>

class Time
{
public:
    Time();
    Time(int, int, int, int, int);
    bool operator<(const Time &) const;
    bool operator==(const Time &) const;
    bool isLeap(int) const;
    //int monthDays(int, int) const;
    int monthDays() const;
    bool checkDate(struct tm) const;
    int dayNumber() const;

    struct tm time;
private:
    bool less(const struct tm &, const struct tm &) const;
    bool equal(const struct tm &, const struct tm &) const;
};