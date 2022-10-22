#pragma once
#include <string>
#include <random>
#include <cstring>
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
    input = g_->convert_input(actor_, 1);
    if (input == "1") {
        buy_barrier();
    } else if (input == "2") {
        buy_robot();
    } else if (input == "3") {
        buy_bomb();
    }
} //进入道具屋

void Player::got_gift_house() {
    g_->out_tip(GiftHouseTip);
    std::string input;
    input = g_->convert_input(actor_, 1);

    if (input == "1") {
        increase_property();
        g_->out_tip(GetFundStr);
    } else if (input == "2") {
        increase_credit();
        g_->out_tip(GetCreditStr);
    } else if (input == "3") {
        increase_god();
        g_->out_tip(GetGodStr);
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
    change_map(HOSPITAL_POS, actor_, get_clour(actor_));
} //遇到炸弹后进入医院

bool Player::sell_land(int loc) {
    if (loc < 0 || loc > 69) {
        g_->out_tip(SellErrorPosLand);
        return false;
    }
    if (g_->places_[loc].owner_ != actor_) {
        g_->out_tip(SellErrorOwnerLand);
        return false;
    }
    property_ += g_->places_[loc].price_ / 2;
    for (auto iter = places_.begin(); iter != places_.end(); iter++) { //从vector中删除指定的某一个元素
        if (*iter == loc) {
            places_.erase(iter);
            break;
        }
    }

    g_->places_[loc].owner_ = '0';
    if (g_->places_[loc].level_ != 0) {
        g_->places_[loc].price_ /= g_->places_[loc].level_;
    }
    g_->places_[loc].level_ = 0;
    g_->out_tip(SellStr);
    change_map(loc, '0', COLOR_BASIC);
    return false;
}
//买地
bool Player::buy_land() {
    while (1) {
        g_->out_tip(QueryBuyEmptyTip);
        auto input = g_->convert_input(actor_, 3);
        if (to_lower(input) == "y") {
            if ((property_ - g_->places_[position_].price_) < 0) {
                g_->out_tip(MoneyNotEnough);
                get_input(0,0,0,0);
                break;
            }
            property_ -= g_->places_[position_].price_;
            places_.push_back(position_);
            g_->places_[position_].state_ = owned;
            g_->places_[position_].owner_ = actor_;
            change_map(position_, g_->places_[position_].default_symbol_, get_clour(actor_));
            g_->out_tip(BuyEmptyY);
            get_input(0,0,0,0);
            break;
        } else if (to_lower(input) == "n") {
            break;
        }
    }
    return true;
}

bool Player::charge(char owner) {
    auto land_price = g_->places_[position_].price_;
    if (land_price > property_) {
        state_ = bankrupt;
        g_->user_num_--;
        if (!bankrupted()) {
            return false;
        }
        g_->out_tip(get_name(actor_) + BankruptcyStr);
        get_input(0,0,0,0);
        return true;
    }
    if (god_ > 0) {
        god_--;
        g_->out_tip(GodOnBodyStr);
        get_input(0,0,0,0);
        return true;
    }
    property_ -= (land_price) / 2;
    g_->players_[owner].property_ += land_price/2;
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

bool Player::user_robot() {
    if (robot_ <= 0) {
        g_->out_tip(NoRobotStr);
        return false;
    } else {
        robot_--;
        for (int i = 1; i <= 10; i++) {
            int pos = (get_position() + i) % PLACE_NUM;
            if (g_->places_[pos].has_bomb != false || g_->places_[pos].has_barrier != false) {
                g_->places_[pos].has_bomb = false;
                g_->places_[pos].has_barrier = false;
                switch (g_->places_[pos].type_) {
                case mine: {
                    change_map(pos, MINE_PIC, COLOR_BASIC);
                    break;
                }
                case tool_house: {
                    change_map(pos, TOOL_PIC, COLOR_BASIC);
                    break;
                }
                case gift_house: {
                    change_map(pos, GIFT_PIC, COLOR_BASIC);
                    break;
                }
                case magic_house: {
                    change_map(pos, MAGIC_PIC, COLOR_BASIC);
                    break;
                }
                case common: {
                    if (g_->places_[pos].state_ == unowned) {
                        change_map(pos, EMPTY_PIC, COLOR_BASIC);
                    } else {
                        char pic;
                        int color;
                        pic = '0' + g_->places_[pos].level_;
                        switch (g_->places_[pos].owner_) {
                        case 0:
                            color = COLOR_Q;
                        case 1:
                            color = COLOR_A;
                        case 2:
                            color = COLOR_S;
                        case 3:
                            color = COLOR_J;
                        }
                        change_map(pos, pic, color);
                    }
                }
                }
            }
        }
        return true;
    }
} // 使用机器人

bool Player::user_bomb(int loc) {
    if (bomb_ <= 0) {
        g_->out_tip(NoBombStr);
        return false;
    } else {
        if (loc < 0 || loc > 69 || (abs(loc - position_) > 10) || g_->places_[position_].has_barrier || g_->places_[position_].has_bomb || g_->places_[position_].has_player != 0 || g_->places_[position_].type_ == hospital || g_->places_[position_].type_ == prision) {
            // 判断loc是否属于[0, 69]
            // 判断loc是否和当前位置差距 > 10
            // 判断loc是否有人、有道具
            // 判断loc是否在医院、监狱
            g_->out_tip(CantPlaceBomb);
            return false;
        } else {
            bomb_--;
            g_->place_tool(loc, TOOL_BOMB);
            change_map(loc, BOMB_PIC, COLOR_BASIC);
            return true;
        }
    }
} // 使用炸弹

bool Player::use_barrier(int loc) {
    if (barrier_ <= 0) {
        g_->out_tip(NoBarrierStr);
        return false;
    } else {
        if (loc < 0 || loc > 69 || (abs(loc - position_) > 10) || g_->places_[position_].has_barrier || g_->places_[position_].has_bomb || g_->places_[position_].has_player != 0 || g_->places_[position_].type_ == hospital || g_->places_[position_].type_ == prision) {
            // 判断loc是否属于[0, 69]
            // 判断loc是否和当前位置差距 > 10
            // 判断loc是否有人、有道具
            // 判断loc是否在医院、监狱
            g_->out_tip(CantPlaceBarrier);
            return false;
        } else {
            barrier_--;
            g_->place_tool(loc, TOOL_BARRIER);
            change_map(loc, BARRIER_PIC, COLOR_BASIC);
            return true;
        }
    }
} // 放置障碍
bool Player::query() {
    std::string str;
    int total[4] = {0};
    std::string s1 = "您现在拥有如下资产：\n资金：";
    std::string s2 = "元\n点数：";
    std::string s3 = "点\n固定资产：\n";
    str = s1 + std::to_string(property_) + s2 + std::to_string(credit_) + s3 + QueryTitleStr + "\n";
    for (int i = 0; i < places_.size(); i++) {
        std::string str_pos;
        int pos = places_[i];
        std::string district;
        if (pos < 28) {
            district = "1";
        } else if (pos < 35) {
            district = "2";
        } else {
            district = "3";
        }
        int level = g_->places_[pos].level_;
        std::string LandLevel;
        switch (level) {
        case 0:
            LandLevel = LandEmptyStr;
            total[0]++;
            break;
        case 1:
            LandLevel = LandLevel1Str;
            total[1]++;
            break;
        case 2:
            LandLevel = LandLevel2Str;
            total[2]++;
            break;
        case 3:
            LandLevel = LandLevel3Str;
            total[3]++;
            break;
        default:
            break;
        }
        str_pos = std::to_string(pos) + "\t" + LandTypeStr + district + "\t" + LandLevel + "\n";
        str += str_pos;
    }
    std::string s4 = "总计：空地" + std::to_string(total[0]) + "块，茅屋：" + std::to_string(total[1]) + "间，洋房：" + std::to_string(total[2]) + "幢，摩天楼：" + std::to_string(total[3]) + "座\n";
    str += s4;
    std::string s5 = "道具：\n炸弹：" + std::to_string(bomb_) + "个\t路障：" + std::to_string(barrier_) + "个\t机器娃娃：" + std::to_string(robot_) + "个\n";
    str += s5;

    // char str_char[500];
    // strcpy(str_char, str.c_str());
    //init_tips(str_char, COLOR_BASIC);
    //show_tips();
    g_->out_tip(str);
} // 查询财产信息
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