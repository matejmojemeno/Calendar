#include <ncurses.h>
#include <string>
#include <cstring>

#define highlight COLOR_PAIR(1)

class Controls {
public:
    void initNcurses() const;
    void endNcurses() const;
    void showCursor() const;
    void stopCursor() const;
private:
    void initColors() const;
};