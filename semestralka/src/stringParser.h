#include <string>
#include <cstring>
#include <vector>
#include <fstream>

#include "time.h"
#include "controls.h"

typedef std::string::iterator strItr;

class Parser
{
public:
    Time parseDate() const;
    std::string getString() const;
    std::vector<std::string> parseParticipants() const;
    std::string trimString(std::string &) const;
    std::vector<std::string> getVector(std::string &) const;


private:
    std::string convertString(char []) const;
    strItr leftTrim(std::string &) const;
    strItr rightTrim(std::string &, const strItr) const;
    void insertString(std::vector<std::string> &, std::string &) const;
};