#pragma once
#include <string>
#include <random>
#include "player.h"
#include "common.h"
#include "gsystem.h"
#include "tips.h"

Player::~Player() {
}
Player::Player() {
}
bool Player::query_use_tool() {
    if (bomb_ > 0 || barrier_ > 0 || robot_ > 0) {
        return true;
    }
    return false;
}

bool Player::increase_credit() {
    credit_ += GIFT_CREDIT;
    return true;
}

int Player::get_credit() {
    return credit_;
}

int Player::update_poistion(int &step_num) {
} //更新位置，

inline char Player::get_name() {
} //获取玩家姓名

inline int Player::get_property() {
} //获取当前财产数

//获取当前状态
bool Player::isBankruptcy(void) {
} //是否破产

bool Player::increase_property() {
} //礼品屋选择金钱

bool Player::increase_god() {
} //礼品屋选择财神
bool Player::buy_bomb() {
} //购买炸弹
bool Player::buy_robot() {
} //购买娃娃
bool Player::buy_barrier() {
} //购买障碍物

void Player::got_tool_house() {
    g->out_tip(ToolHouseTip);
    std::string input;

    if (input == "1") {
        increase_property();
    }else if (input == "2") {
        increase_credit();
    }else if (input == "3") {
        increase_god();
    }
    
} //进入道具屋
void Player::got_gift_house() {
    g->out_tip(GiftHouseTip);
    std::string input;
    // input = g->convert_input(actor_, 1);
    
    while(1) {
        input = g->convert_input(actor_);
        if (input == "1") {
            buy_barrier();
        }else if (input == "2") {
            buy_robot();
        }else if (input == "3") {
            buy_bomb();
        }else {
            break;
        }
    }
} //进入礼物屋
void Player::got_prison() {
    stop_time_ += PRISON_ROLL_DELAY;
} //进入监狱
void Player::got_mine() {
    switch (position_) {
        case MINE1_POS: {
            credit_ += MINE1_CREDIT;
            break;
        }
        case MINE2_POS: {
            credit_ += MINE2_CREDIT;
            break;
        }
        case MINE3_POS: {
            credit_ += MINE3_CREDIT;
            break;
        }case MINE4_POS: {
            credit_ += MINE4_CREDIT;
            break;
        }
        case MINE5_POS: {
            credit_ += MINE5_CREDIT;
            break;
        }
        case MINE6_POS: {
            credit_ += MINE6_CREDIT;
            break;
        }
    }
} //到达矿地
void Player::got_hospital() {
    stop_time_ += HOSPITAL_ROLL_DELAY;
    position_ = HOSPITAL_POS;
} //遇到炸弹后进入医院
void Player::barriered() {
} //遇到障碍
bool Player::sell_land() {
} //卖地
bool Player::buy_land() {
    g->places_[40].set_owner(actor_);
    return true;

} //买地
bool Player::charge() {
} //玩家缴费
bool Player::stopped() {
} //因为炸弹或监狱等状态轮空一轮

bool Player::query_buy_empty() {
} //查询是否买空地，（查询是否符合买地条件）

bool Player::query_update_lands() {
} //查询是否升级建筑
bool Player::query_sell_lands() {
} //查询是否出卖地产
