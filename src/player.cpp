#pragma once
#include <string>
#include <random>
#include "player.h"
#include "common.h"
#include "gsystem.h"

Player::~Player() {
}
Player::Player() {
}

bool Player::update_poistion(int &) {
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

bool Player::isBankruptcy(void) {
    return state_ == bankrupt ? true : false;
}
bool Player::increase_property() {
    property_ += 2000;
    return true;
}

bool Player::increase_god() {
    god_ += 5;
    return true;
}
bool Player::buy_bomb() {
    if (property_ >= 50 && (bomb_ + robot_ + barrier_) < 10) {
        property_ -= 50;
        bomb_ += 1;
        return true;
    } else {
        return false;
    }
}
bool Player::buy_robot() {
    if (property_ >= 30 && (bomb_ + robot_ + barrier_) < 10) {
        property_ -= 30;
        robot_ += 1;
        return true;
    } else {
        return false;
    }
}

bool Player::buy_barrier() {
    if (property_ >= 50 && (bomb_ + robot_ + barrier_) < 10) {
        property_ -= 50;
        barrier_ += 1;
        return true;
    } else {
        return false;
    }
}

void Player::got_tool_house() {
} //进入道具屋
void Player::got_gift_house() {
} //进入礼物屋
void Player::got_prison() {
} //进入监狱
void Player::got_mine() {
} //到达矿地
void Player::got_hospital() {
} //遇到炸弹后进入医院
void Player::got_barriered() {
} //遇到障碍
bool Player::sell_land() {
} //卖地
bool Player::buy_land() {
} //买地
bool Player::charge() {
} //玩家缴费
bool Player::stopped() {
} //因为炸弹或监狱等状态轮空一轮