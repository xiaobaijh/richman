#pragma once
#include <string>
#include "player.h"

enum place_state { unowned,
                   owned,
                   bombed,
                   barried,
};

enum place_type {
    common,
    hospital,
    prision,
    mine,
    tool_house,
    gift_house,
    magic_house
};

class Place {
public:
    place_state state_{unowned};
    place_type type_{common};
    char owner_{'0'}; // owner =0没有所有者，1表示玩家1，类推
    int price_{0};
    int level_{0};
    bool has_player{false}; //是否有玩家

    Place() = default;
    ~Place();

    void init(void);
    inline place_state get_state() {
        return state_;
    }
    inline bool set_state(place_state state);
    inline bool set_owner(char owner) {
        owner_ = owner;
        return false;
    }
    inline char get_owner() {
        return owner_;
    }
    inline int get_price();
    inline int get_level();
    inline int update();

private:
};
