#pragma once
#include <string>
#include "player.h"

enum place_state { unowned,
                   owned,
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
    place_state state_{owned};
    place_type type_{common};
    char owner_{'0'}; // owner =0没有所有者，1表示角色1，类推
    int price_{0};
    int level_{0};
    bool has_player{false}; //是否有玩家
    bool has_bomb{false}; //是否有炸弹
    bool has_barrier{false}; //是否有障碍

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
