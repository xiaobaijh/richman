#pragma once
#include "place.h"
#include "player.h"
#include "display.h"
#include "common.h"
#include <cstddef>
#include <valarray>
#include <vector>
#include <unordered_map>

class Player;
class Place;

class Gsystem {
    friend class Place;
    friend class Player;

private:
    std::size_t user_num_{0};
    std::string user_order_;
    std::string map_[70]; //供绘图模块使用
    Place places_[PLACE_NUM];
    std::unordered_map<char, Player> players_;
    char current_player_{0};

public:
    Gsystem();
    virtual ~Gsystem(void);
    void init_places(void); //初始化地形
    void init_map();
    void reset_game(void); //重置游戏
    bool Ready();

    void out_tips(std::string &tip);
    void out_err(std::string &tip);
    int parse_input(std::string &input);
    bool set_default_fund(int &num);
    bool set_user(std::string seq); //设置玩家列表

    bool step();
    int player_step(Player &player);
    int get_dices();                                          //模拟掷骰子
    bool use_tool(int loc, int type);                         //使用道具
    place_type update_position(Player &player, int position); //根据位置更新玩家信息，考虑地形，
                                                              //在这里修改玩家状态，返回结束后所在地形特征
};