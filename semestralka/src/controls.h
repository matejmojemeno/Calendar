#include <ncurses.h>

class Controls {
public:
    void initNcurses();
    int readKey();
};