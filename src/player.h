#pragma once
#include <iostream>
#include <valarray>
#include <vector>
#include "place.h"

enum player_state { normal,
                    bankrupt,
                    stop };
class Gsystem;
class Player {
public:
    Player();
    Player(char actor, int property) {
        actor_ = actor;
        property_ = property;
    }
    ~Player();
    bool update_poistion(int &step_num); //更新位置，

    inline int get_position() {
        return position_;
    } //获取当当前位置
    inline int get_property() {
        return property_;
    } //获取当前财产数
    inline int get_credit() {
        return credit_;
    } //获取当前积分数
    inline player_state get_state() {
        return state_;
    } //获取当前状态
    inline int get_stop_time() {
        return stop_time_;
    }
    inline int get_barrier() {
        return barrier_;
    }
    inline int get_god() {
        return god_;
    }
    inline int get_robot() {
        return robot_;
    }

    inline bool increase_land(int &loc) {
        places_.push_back(loc);
        return true;
    }

    void decrease_god() {
        god_--;
    }

    bool isBankruptcy(void); //是否破产

    bool increase_property(); //礼品屋选择金钱
    bool increase_credit();   //礼品屋选则积分
    bool increase_god();      //礼品屋选择财神
    bool buy_robot();         //购买娃娃
    bool buy_barrier();       //购买障碍物

    void got_tool_house();   //进入道具屋
    void got_gift_house();   //进入礼物屋
    void got_prison();       //进入监狱
    void got_mine();         //到达矿地
    void got_magic_house();  //到达魔法屋
    bool sell_land(int loc); //卖地
    bool buy_land();         //买地
    bool charge(char owner); //玩家缴费
    bool bankrupted();       //玩家破产
    bool stopped();          //因为炸弹或监狱等状态轮空一轮
    bool update_land();      //升级土地

    bool query_buy_empty();    //查询是否买空地，（查询是否符合买地条件）
    bool query_use_tool();     //查询是否使用道具
    bool query_update_lands(); //查询是否升级建筑
    bool query_sell_lands();   //查询是否出卖地产

    bool user_robot();         //使用机器人
    bool use_barrier(int loc); //放置障碍
    bool query();              //查询财产信息

    bool set_pos(int &num);
    bool set_property(int &num);
    bool set_credit(int &num);
    bool set_stop_time_(int &num);
    bool set_barrier(int &num);
    bool set_robot(int &num);
    bool set_god(int &num);
    bool add_stop_time(int num);
    void init(Gsystem *g) {
        g_ = g;
    }

    Gsystem *g_;
    player_state state_{normal};
    char actor_{'0'};

private:
    int position_{0};         //位置
    int property_{0};         //金钱数
    int credit_{0};           //积分数
    int stop_time_{0};        //剩余停止轮数
    int barrier_{0};          //障碍数
    int robot_{0};            //机器人数
    int god_{0};              //财神剩余回
    std::vector<int> places_; //玩家拥有的地块,编号
};
