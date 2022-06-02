#include "stringParser.h"

std::string Parser::getString() const
{
    Controls n;
    n.showCursor();

    char string[42];
    attron(COLOR_PAIR(2));
    getnstr(string, 42);
    attroff(COLOR_PAIR(2));
    n.stopCursor();

    return convertString(string);
}

std::string Parser::convertString(char string[]) const
{
    std::string newString;
    int pos = 0;

    while (*string)
        newString.push_back(*string++);

    return newString;
}

Time Parser::parseDate() const
{
    int year, mon, day, hour, min;
    std::string date = getString();

    sscanf(date.c_str(), "%d.%d.%d %d:%d", &day, &mon, &year, &hour, &min);

    Time time(year, mon, day, hour, min);
    return time;
}

std::string Parser::parseName() const
{
    return getString();
}

std::string Parser::parsePlace() const
{
    return getString();
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
    size_t pos = 0;
    std::vector<std::string> participants;
    std::string str = getString(), token;

    while ((pos = str.find(',')) != std::string::npos)
    {
        token = str.substr(0, pos);
        insertString(participants, token);
        str.erase(0, pos + 1);
    }
    insertString(participants, token);

    return participants;
}