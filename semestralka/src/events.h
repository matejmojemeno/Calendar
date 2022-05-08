#include <map>
#include "time.h"

class Events {
public:
    virtual void createEvent(const std::string & ,const Time &);
    virtual void deleteEvent (const Time &);
    virtual void deleteEvent (const std::string &);
    virtual void moveEvent (const Time &);
    virtual void moveEvent (const std::string &);
private:
  std::map<std::string, Time> events;  
};