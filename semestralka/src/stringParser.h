#include <string>
#include <cstring>
#include <vector>
#include <ncurses.h>

#include "time.h"
#include "controls.h"

typedef std::string::iterator strItr;

class Parser
{
public:
    void readFile();
    Time parseDate() const;
    std::string parseName() const;
    std::string parsePlace() const;
    std::vector<std::string> parseParticipants() const;
private:
    std::string getString() const;
    std::string convertString(char []) const;
    std::string trimString(std::string &) const;
    strItr leftTrim(std::string &) const;
    strItr rightTrim(std::string &, const strItr) const;
    void insertString(std::vector<std::string> &, std::string &) const;
};