#pragma once
#include <string>
#include "player.h"

enum place_state { unowned,
                   owned,
                   mortgaged,
};

class Place {
public:
    Place(std::string name, int price) {
        name_ = name;
        price_ = price;
        state_ = unowned;
    }
    ~Place();
    virtual void special_func();

    place_state state_;
    std::string name_;
    int position; //地点自己的编号
    Player owner_;
    money price_;
    typedef struct {
        int level;
        money price;
    } house;

private:
};