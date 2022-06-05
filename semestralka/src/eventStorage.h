#include <memory>
#include <algorithm>
#include "event.h"

#define DAY 1
#define WEEK 7
#define TWOWEEKS 14

class EventStorage
{
public:
    void addEvent(const Event &);
    std::vector<Event> dayEvents(const Time &) const;
    void findName(const std::string &, bool &, Event &) const;

    std::vector<Event> allEvents;
    std::vector<Event> eventsByStart;
    std::vector<Event> dailyEvents;
    std::vector<Event> weeklyEvents;
    std::vector<Event> twoWeeklyEvent;
    std::vector<Event> monthlyEvents;

private:
    bool checkEvent(const Event &) const;
    bool checkDate(const Event &) const;
    bool checkName(const std::string &) const;
    void newName(const Event &);
    bool iterateEvents(const Event &, const std::vector<Event> &) const;
    std::vector<Event> genRepeated(const Event &) const;
    bool emptyRepeated() const;
    bool intersectEvent(const Event &, const Event &) const;
    void insert(const Event &);
    void insertStart(const Event &);
    void insertRepeated(const Event &);
    void sameDay(std::vector<Event> &, const Time &) const;
    void sameDayReps(std::vector<Event> &, const Time &) const;
    void sameWeekReps(std::vector<Event> &, const Time &) const;
    void sameTwoWeekReps(std::vector<Event> &, const Time &) const;
    void sameMonthReps(std::vector<Event> &, const Time &) const;
};