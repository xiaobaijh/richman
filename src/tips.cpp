#include "tips.h"
#include "common.h"
#include <string>
std::string get_name(char c) {
    switch (c) {
    case 'A':
        return "阿土伯";
    case 'Q':
        return "钱夫人";
    case 'S':
        return "孙小美";
    case 'J':
        return "金贝贝";
    default:
        return "";
    }
}

std::string get_level_str(int level) {
    switch (level) {
    case LEVEL0:
        return LandEmptyStr;
    case LEVEL1:
        return LandLevel1Str;
    case LEVEL2:
        return LandLevel2Str;
    case LEVEL3:
        return LandLevel3Str;

    default:
        return "";
    }
}

int get_clour(char c) {
    switch (c) {
    case 'a':
        return COLOR_A;
    case 'q':
        return COLOR_Q;
    case 's':
        return COLOR_S;
    case 'j':
        return COLOR_J;
    default:
        return 0;
    }
}
