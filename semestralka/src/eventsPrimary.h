#include "events.h"

class EventsPrimary : public Events {
    void createEvent(const std::string & ,const Time &) override;
    void deleteEvent (const Time &) override;
    void deleteEvent (const std::string &) override;
    void moveEvent (const Time &) override;
    void moveEvent (const std::string &) override;
};