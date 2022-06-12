#include <ncurses.h>
#include <string>
#include <cstring>

#define HIGHLIGHT COLOR_PAIR(1)
#define INPUT COLOR_PAIR(2)
#define ERROR COLOR_PAIR(3)
#define BLUE COLOR_PAIR(4)

/**
 * @brief 
 * class to make basic ncurses instructions
 */
class Controls {
public:
    /**
     * @brief 
     * initializes ncurses libary
     */
    void initNcurses() const;
    /**
     * @brief 
     * ends ncurses library
     */
    void endNcurses() const;
    /**
     * @brief 
     * functions to show and stop showing cursos
     */
    void showCursor() const;
    void stopCursor() const;
private:
    /**
     * @brief 
     * initializes all color pairs
     */
    void initColors() const;
};