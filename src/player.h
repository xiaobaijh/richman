#pragma once
#include <iostream>
#include <valarray>
#include <vector>

enum player_state { normal,
                    bankrupt,
                    stop };

class Player {
public:
    Player(int property, int credit) {
        property_ = property;
        credit_ = credit;
        state_ = normal;
        position_ = 0;
        stop_time_ = 0;
    }
    ~Player();
    std::string get_name();
    int get_dices();                     //模拟掷骰子
    void update_poistion(int &step_num); //更新位置，

    player_state state_;
    int position_;
    int property_;
    int credit_;

private:
    int stop_time_ = 0;
    std::valarray<int> props_[3]; //props_[0]炸弹数量，props_[1]娃娃数量，props_[0]路障数量，
    std::vector<int> places_;     //玩家拥有的地块,编号
};
