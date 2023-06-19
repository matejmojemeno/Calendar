#include "stringParser.h"

std::string Parser::getString() const
{
    Controls n;
    n.showCursor();
    int x, y;
    getyx(stdscr, y, x);

    char string[60];
    attron(COLOR_PAIR(2));
    getnstr(string, 60);
    attroff(COLOR_PAIR(2));
    n.stopCursor();

    std::string newString = convertString(string);
    if (newString == "") {
        move(y, x);
        return getString();
    }

    return newString;
}

std::string Parser::convertString(char string[]) const
{
    std::string newString;

    while (*string)
        newString.push_back(*string++);

    return newString;
}

Time Parser::parseDate() const
{
    char year[255];
    int mon, day, hour, min;
    std::string date = getString();

    if (! sscanf(date.c_str(), "%d.%d.%s %d:%d", &day, &mon, year, &hour, &min))
        throw std::invalid_argument("Invalid date or format.");

    Time time(year, mon, day, hour, min);
    return time;
}

strItr Parser::leftTrim(std::string &str) const
{
    strItr start = str.begin();
    while (start != str.end() && std::isspace(*start))
    {
        start++;
    }

    return start;
}

strItr Parser::rightTrim(std::string &str, const strItr start) const
{
    strItr end = str.end();
    do
    {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return end;
}

std::string Parser::trimString(std::string &str) const
{
    strItr start = leftTrim(str);
    return std::string(start, rightTrim(str, start) + 1);
}

void Parser::insertString(std::vector<std::string> &participanst, std::string &token) const
{
    std::string str = trimString(token);
    if (str != "")
        participanst.push_back(str);
}

std::vector<std::string> Parser::parseParticipants() const
{
    std::string str = getString(), token;

    return getVector(str);
}

std::vector<std::string> Parser::getVector(std::string &str) const {
    std::vector<std::string> participants;
    std::string token;
    size_t pos = 0;

    while ((pos = str.find(',')) != std::string::npos)
    {
        token = str.substr(0, pos);
        insertString(participants, token);
        str.erase(0, pos + 1);
    }
    insertString(participants, str);

    return participants;
}