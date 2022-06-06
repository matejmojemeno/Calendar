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
    /**
     * @brief 
     * converts string to a date
     * @return Time 
     */
    Time parseDate() const;
    /**
     * @brief Get the String object
     * reads a string from input
     * @return std::string 
     */
    std::string getString() const;
    /**
     * @brief 
     * reads input and converts it to a vector
     * @return std::vector<std::string> 
     */
    std::vector<std::string> parseParticipants() const;
    /**
     * @brief 
     * trims excessive spaces in front and at back of string
     * @return std::string 
     */
    std::string trimString(std::string &) const;
    /**
     * @brief Get the Vector object
     * turns string into vector
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getVector(std::string &) const;


private:
    /**
     * @brief 
     * converts char[] to std::string
     * @return std::string 
     */
    std::string convertString(char []) const;
    /**
     * @brief 
     * functions called by trimString
     * @return strItr 
     */
    strItr leftTrim(std::string &) const;
    strItr rightTrim(std::string &, const strItr) const;
    /**
     * @brief 
     * first checks if string isnt empty
     */
    void insertString(std::vector<std::string> &, std::string &) const;
};