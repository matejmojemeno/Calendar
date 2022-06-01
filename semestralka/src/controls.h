#include <ncurses.h>
#include <string>
#include <cstring>

class Controls {
public:
    void initNcurses() const;
    std::string getString() const;
    void endNcurses() const;
private:
    std::string convertString(char[]) const;    
};