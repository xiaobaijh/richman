#pragma once
#include <iostream>
#include <vector>

typedef int money;

enum player_state { normal,
                    bankrupt };

class Player {
public:
    explicit Player();
    Player(std::string name) {
        name_ = name;
        state_ = normal;
    }
    ~Player();
    std::string get_name();
    void buy(int place_num); //参数地图中编号,sell和buy针对买地和抵押
    void sell(int place_num);
    void decrease_money(money mount);    //到达地图后check地图状态后先扣自己的钱
    void charge(Player &other_player);   //向地图owner缴费
    void update_place();                 //根据地图编号升级地图,访问自己的places数组
    int get_dices();                     //模拟掷骰子
    void update_poistion(int &step_num); //更新位置，

    std::string name_;
    player_state state_;
    int position_;
    std::vector<int> places;

    money proverty_;

private:
};
