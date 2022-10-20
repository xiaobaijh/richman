#include "gutil.h"
#include "common.h"
#include <regex>

std::string to_lower(std::string s)
{
    for (auto &e : s)
        e = tolower(e);
    return s;
}
std::string to_upper(std::string s)
{
    for (auto &e : s)
        e = toupper(e);
    return s;
}
bool isPlayerName(char c)
{
    return c == 'q' || c == 'a' || c == 's' || c == 'j';
}
char GetPlayerName(int idx)
{
    switch (idx)
    {
    case '1':
        return 'Q';
    case '2':
        return 'A';
    case '3':
        return 'S';
    case '4':
        return 'J';
    default:
        return '\0';
    }
}

