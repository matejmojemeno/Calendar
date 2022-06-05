#include <ncurses.h>
#include <string>
#include <cstring>

#define HIGHLIGHT COLOR_PAIR(1)
#define INPUT COLOR_PAIR(2)
#define ERROR COLOR_PAIR(3)
#define BLUE COLOR_PAIR(4)

class Controls {
public:
    void initNcurses() const;
    void endNcurses() const;
    void showCursor() const;
    void stopCursor() const;
private:
    void initColors() const;
};