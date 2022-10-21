#pragma once
#include <string>
#include <random>
#include "player.h"
#include "common.h"
#include "gsystem.h"
#include "tips.h"
#include "gutil.h"
#include "display.h"

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
    change_map(HOSPITAL_POS, actor_, 0);
} //遇到炸弹后进入医院

bool Player::sell_land() {
}
//买地
bool Player::buy_land() {
    while (1) {
        g_->out_tip(QueryBuyEmptyTip);
        auto input = g_->convert_input(actor_, 3);
        if (to_lower(input) == "y") {
            if ((property_ - g_->places_[position_].price_) < 0) {
                g_->out_tip(MoneyNotEnough);
                break;
            }
            property_ -= g_->places_[position_].price_;
            places_.push_back(position_);
            g_->places_[position_].state_ = owned;
            g_->places_[position_].owner_ = actor_;
            change_map(position_, g_->places_[position_].default_symbol_, 0);
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
    auto land_price = g_->places_[position_].price_;
    if (land_price > property_) {
        state_ = bankrupt;
        g_->user_num_--;
        if (!bankrupted()) {
            return false;
        }
        g_->out_tip(get_name(actor_) + BankruptcyStr);
        return true;
    }
    if (god_ > 0) {
        god_--;
        g_->out_tip(GodOnBodyStr);
        return true;
    }
    property_ -= land_price;
    g_->players_[actor_].property_ += land_price;
    return true;
} //玩家缴费

bool Player::bankrupted() {
    for (auto iter = places_.begin(); iter != places_.end(); iter++) {
        g_->places_[*iter].owner_ = '0';
        g_->places_[*iter].state_ = unowned;
        auto price = g_->places_[*iter].price_;
        if (g_->places_[*iter].level_ != 0) {
            g_->places_[*iter].price_ /= g_->places_[*iter].level_;
        }
        g_->places_[*iter].level_ = 0;
        change_map(*iter, '0', COLOR_BASIC);
    }
    return true;
}
bool Player::stopped() {
    stop_time_--;
    stop_time_ == 0 ? state_ = normal : state_ = stop;
    return true;
} //因为炸弹或监狱等状态轮空一轮

bool Player::update_land() {
    auto land_price = g_->places_[position_].price_;
    if (land_price > property_) {
        return true;
    }
    while (1) {
        if (g_->places_[position_].level_ < 4) {
            g_->out_tip(QueryUpdateBulidingTip);
            auto input = g_->convert_input(actor_, 1);
            if (input == "y") {
                property_ -= land_price;
                land_price += land_price;
                g_->places_[position_].level_++;
                g_->out_tip(get_name(actor_) + UpdateBulidingY);
                break;
            } else if (input == "n") {
                break;
            }
        }
    } //升级土地
    return true;
}

bool Player::set_pos(int &num) {
    position_ = num;
    return true;
}
bool Player::set_property(int &num) {
    property_ = num;
    return true;
}
bool Player::set_credit(int &num) {
    credit_ = num;
    return true;
}
bool Player::set_stop_time_(int &num) {
    stop_time_ = num;
    return true;
}
bool Player::set_bomb(int &num) {
    bomb_ = num;
    return true;
}
bool Player::set_barrier(int &num) {
    barrier_ = num;
    return true;
}
bool Player::set_robot(int &num) {
    robot_ = num;
    return true;
}
bool Player::set_god(int &num) {
    god_ = num;
    return true;
}