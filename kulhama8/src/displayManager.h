#include <map>

#include "displayMonth.h"

class DisplayManager
{
public:
    void display(const EventStorage &) const;
private:
    static const std::map<std::string, std::shared_ptr<Display>> displays;
};