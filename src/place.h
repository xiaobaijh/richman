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
    Place(int price) {
        price_ = price;
        state_ = unowned;
    };
    ~Place();

    void init(void);
    inline place_state get_state() {
        return state_;
    }
    inline bool set_state(place_state state);
    inline int get_owner();
    inline int get_price();
    inline int get_level();
    inline int update();

private:
    place_state state_;
    char owner_{0}; //owner =0没有所有者，1表示玩家1，类推
    int price_{0};
    int level_{0};
};
