#pragma once
#include <string>
#include "player.h"

enum place_state { unowned,
                   owned,
                   mortgaged,
                   bombed,
                   barried,
};

enum place_type {
    common,
    hospital,
    posion,
    mine,
    prop_house,
    gift_house,
    magic_house
};

class Base {
public:
    Base() = default;
    Base(int position) {
        position_ = position;
    }
    ~Base();
    int position_;
    bool occpuied; //是否被占用
    place_type type_;
    virtual void special_func(void);
};

class Place : public Base {
public:
    Place(int price) {
        price_ = price;
        state_ = unowned;
    };
    ~Place();

    place_state state_;
    int owner_; //owner =0没有所有者，1表示玩家1，类推
    int price_;
    typedef struct {
        int level;
        int price;
    } house;
    void buy(Player &player);
    void update();
    void sell(Player &player);
    void charge(Player &player); //交租金

private:
};

class Gift_house : public Base {
public:
    virtual void buy(Player &player);
};

class Posion : public Base {
public:
    virtual void special_func(Player &player);
};

class Hospital : public Base {
public:
    virtual void special_func(Player &player);
};

class Mine : public Base {
public:
    virtual void special_func(Player &player);
};
