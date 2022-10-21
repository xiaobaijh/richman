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
    return c == 'Q' || c == 'A' || c == 'S' || c == 'J';
}
