#pragma once
#include <string>
#include "player.h"
#include "display.h"

enum place_state { unowned,
                   owned,
};

enum place_type {
    common,
    mine,
    tool_house,
    gift_house,
    magic_house,
    park,
    start
};

class Place {
public:
    place_state state_{unowned};
    place_type type_{common};
    char default_symbol_{'0'}; //地图默认图标
    int color_{COLOR_BASIC};
    char owner_{'0'}; // owner =0没有所有者，1表示玩家1，类推
    int price_{0};
    int level_{0};
    int has_player{0}; //是否有玩家
    bool has_barrier{false};

    Place() = default;
    ~Place();

private:
};
