#pragma once
#include <string>
#include <random>
#include "player.h"
#include "common.h"
#include "gsystem.h"
#include "tips.h"
#include "gutil.h"

Player::~Player() {
}
Player::Player() {
}

bool Player::update_poistion(int &step_num) {
    position_ = (position_ + step_num) % 69;
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
    g_->out_tip(ToolHouseTip);
    std::string input;

    if (input == "1") {
        increase_property();
    } else if (input == "2") {
        increase_credit();
    } else if (input == "3") {
        increase_god();
    }

} //进入道具屋
void Player::got_gift_house() {
    g_->out_tip(GiftHouseTip);
    std::string input;
    // input = g->convert_input(actor_, 1);

    while (1) {
        input = g_->convert_input(actor_, 1);
        if (input == "1") {
            buy_barrier();
        } else if (input == "2") {
            buy_robot();
        } else if (input == "3") {
            buy_bomb();
        } else {
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
    }
    case MINE4_POS: {
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
void Player::got_barriered() {
} //遇到障碍
bool Player::sell_land() {
}
//买地
bool Player::buy_land() {
    while (1) {
        g_->out_tip(QueryBuyEmptyTip);
        auto input = g_->convert_input(actor_, 1);
        if (to_lower(input) == "y") {
            if ((property_ - g_->places_[position_].price_) < 0) {
                g_->out_tip(MoneyNotEnough);
                break;
            }
            property_ -= g_->places_[position_].price_;
            g_->places_[position_].state_ = owned;
            g_->places_[position_].set_owner(actor_);
            g_->out_tip(BuyEmptyY);
            break;
        } else if (to_lower(input) == "n") {
            break;
        }
    }
    return true;
}
//买地
bool Player::charge() {
} //玩家缴费
bool Player::stopped() {
} //因为炸弹或监狱等状态轮空一轮