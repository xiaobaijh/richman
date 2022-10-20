#pragma once
#include <iostream>
#include <valarray>
#include <vector>
#include "place.h"

enum player_state { normal,
                    bankrupt,
                    stop };
class Place;
class Player {
    friend class Place;

public:
    Player();
    Player(char actor, int property) {
        actor_ = actor;
        property_ = property;
    }
    ~Player();
    int update_poistion(int &step_num); //更新位置，

    inline char get_name();    //获取玩家姓名
    inline int get_position(); //获取当当前位置
    inline int get_property(); //获取当前财产数
    inline int get_credit();   //获取当前积分数
    inline player_state get_state() {
        return state_;
    }                        //获取当前状态
    bool isBankruptcy(void); //是否破产

    bool increase_property(); //礼品屋选择金钱
    bool increase_credit();   //礼品屋选则积分
    bool increase_god();      //礼品屋选择财神
    bool buy_bomb();          //购买炸弹
    bool buy_robot();         //购买娃娃
    bool buy_barrier();       //购买障碍物

    void got_tool_house();        //进入道具屋
    void got_gift_house();        //进入礼物屋
    void got_prison();            //进入监狱
    void got_mine();              //到达矿地
    void got_hospital();          //遇到炸弹后进入医院
    void barriered();             //遇到障碍
    bool sell_land(Place &place); //卖地
    bool buy_land(Place &place);  //买地
    bool charge(Place &place);    //玩家缴费
    bool stopped();               //因为炸弹或监狱等状态轮空一轮

    bool query_buy_empty();    //查询是否买空地，（查询是否符合买地条件）
    bool query_use_tool();     //查询是否使用道具
    bool query_update_lands(); //查询是否升级建筑
    bool query_sell_lands();   //查询是否出卖地产

    bool player_move(); //玩家移动一步

    player_state state_{normal};
    char actor_{0};

private:
    int position_{0};
    int property_{0};
    int credit_{0};
    int stop_time_{0};        //剩余停止轮数
    int bomb_{0};             //炸弹数
    int barrier_{0};          //障碍数
    int robot_{0};            //机器人数
    int god_{0};              //财神剩余回
    std::vector<int> places_; //玩家拥有的地块,编号
};
