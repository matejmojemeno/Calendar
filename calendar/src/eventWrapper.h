#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

#include "eventStorage.h"

class EventWrapper
{
public:
    /**
     * @brief 
     * create new event
     */
    void newEvent();
    /**
     * @brief 
     * read new event from file
     */
    void newFileEvent();
    /**
     * @brief 
     * manage given group of events
     */
    void manageEvents(std::vector<std::shared_ptr<Event>> &);
    /**
     * @brief 
     * find all events with given name
     * @return std::vector<std::shared_ptr<Event>> 
     */
    std::vector<std::shared_ptr<Event>> eventsByName() const;
    /**
     * @brief 
     * find all events with given place
     * @return std::vector<std::shared_ptr<Event>> 
     */
    std::vector<std::shared_ptr<Event>> eventsByPlace() const;

    EventStorage storage;

private:
    /**
     * @brief 
     * calls function to add event to storage
     */
    void callAddEvent(const Time &, const Time &, const std::string &, const std::string &, const std::vector<std::string> &, int);
    /**
     * @brief Get the Start object
     * group of functions to get event info from user 
     */
    Time getStart() const;
    Time getEnd() const;
    std::string getName() const;
    std::string getPlace() const;
    std::vector<std::string> getParticipants() const;
    int getRepetition() const;
    /**
     * @brief 
     * clears line and moves cursor to the beginning of the line
     */
    void resetLine() const;
    /**
     * @brief 
     * draws menu for picking repetition
     */
    void drawRepMenu(size_t) const;
    /**
     * @brief 
     * updates position of menu picker if needed
     */
    void updatePos(int, size_t &, const size_t &) const;
    /**
     * @brief 
     * checks if certain character is in file
     * @return true 
     * @return false 
     */
    bool checkChar(std::ifstream &, char) const;
    /**
     * @brief Get the File Time object
     * group of functions to get event info from file
     */
    Time getFileTime(std::ifstream &) const;
    std::string getFileString(std::ifstream &) const;
    std::vector<std::string> getFilePart(std::ifstream &) const;
    int getFileRep(std::ifstream &) const;
    /**
     * @brief 
     * calls function chosen by user
     * @return true 
     * @return false 
     */
    bool callFunc(std::shared_ptr<Event>, int);
    /**
     * @brief 
     * displays error message on screen
     */
    void showError(const char *) const;

    Parser p;
    static const std::array<std::string, 5> repMenu;
};