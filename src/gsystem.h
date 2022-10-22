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
    friend std::string CommandFuncPreset(std::string cmd, Gsystem *g);

private:
    char map_[70]{'0'}; //供绘图模块使用
    char input_buffer_[100];

public:
    std::string user_order_{"qasj"};
    Place places_[PLACE_NUM];
    std::unordered_map<char, Player> players_;
    bool game_over_{false};
    char current_player_{'0'};
    std::size_t user_num_{0};

    Gsystem();
    virtual ~Gsystem(void);

    void init_game_display();
    // void init_map();
    bool set_user(std::string &seq, int money); //设置玩家列表
    bool ready();

    void out_tip(std::string tip); //向游戏框输出提示信息
    void out_help();
    void out_err(std::string &tip);                 //系统输出错误，即提示开发人员的错误
    std::string convert_input(char actor, int len); //需要玩家输入信息时使用，返回一个字符串
    int prarse_input(std::string &input);           //处理输入信息，支持处理quit,help两种玩家指令，preset,print两种系统指令

    bool step();                                //游戏进行一步
    int player_step(char actor);                //玩家活动一步
    int get_dices();                            //模拟掷骰子
    bool use_tool(int loc, int type);           //使用道具
    bool update_position(char actor, int step); //根据位置更新玩家信息，考虑地形，

    bool preset(std::string &cmd);                     //以下均为预设置有关
    bool set_current_user(char cur_user);              //设置当前玩家
    bool set_user_pos(char user, int loc);             //设置玩家位置
    bool set_property(char user, int num);             //设置玩家钱
    bool set_credit(char user, int num);               //设置玩家点数
    bool set_state(char user, int num);                //设置玩家停止回合数
    bool set_bomb(char user, int num);                 //设置玩家炸弹数
    bool set_barrier(char user, int num);              //设置玩家路障数
    bool set_robot(char user, int num);                //设置玩家机器人数
    bool set_god(char user, int num);                  //设置财神回合
    bool set_building(int loc, int level, char owner); //设置建筑物状态
    bool place_tool(int loc, int type);                //防止道具1炸弹2路障

    bool print(); //向测试输出 FXXK
};