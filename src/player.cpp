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
    
} //进入道具屋
void Player::got_gift_house() {
    g->out_tip(GiftHouseTip);
    std::string input;
    input = g->convert_input(actor_);

    if (input == "1") {
        increase_property();
        g->out_tip(GetFundStr);
    }else if (input == "2") {
        increase_credit();
        g->out_tip(GetCreditStr);
    }else if (input == "3") {
        increase_god();
        g->out_tip(GetGodStr);
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

bool Player::user_robot() {
    if (robot_ <= 0) {
        g->out_tip(NoRobotStr);
        return false;
    }else {
        robot_ --;
        for (int i = 1; i <= 10; i ++) {
            int pos = (get_position() + i) % PLACE_NUM;
            if (g->places_[pos].has_bomb != false || g->places_[pos].has_barrier != false) {
                g->places_[pos].has_bomb = false;
                g->places_[pos].has_barrier = false;
                switch (g->places_[pos].type_) {
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
                        if (g->places_[pos].state_ == unowned) {
                            change_map(pos, EMPTY_PIC, COLOR_BASIC);
                        }else {
                            char pic;
                            int color;
                            pic = '0' + g->places_[pos].level_;
                            switch (g->places_[pos].owner_) {
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
        g->out_tip(NoBombStr);
        return false;
    }else {
        if (loc < 0 || loc > 69 || (abs(loc - position_) > 10) || g->places_[position_].has_barrier || g->places_[position_].has_bomb || g->places_[position_].has_player || g->places_[position_].type_ == hospital || g->places_[position_].type_ == prision) { 
            // 判断loc是否属于[0, 69]
            // 判断loc是否和当前位置差距 > 10
            // 判断loc是否有人、有道具
            // 判断loc是否在医院、监狱
            g->out_tip(CantPlaceBomb);
            return false;
        }else {
            bomb_ --;
            g->place_tool(loc, TOOL_BOMB);
            change_map(loc, BOMB_PIC, COLOR_BASIC);
            return true;
        }
    }
} // 使用炸弹
bool Player::user_barrier(int loc) {
    if (barrier_ <= 0) {
        g->out_tip(NoBarrierStr);
        return false;
    }else {
        if (loc < 0 || loc > 69 || (abs(loc - position_) > 10) || g->places_[position_].has_barrier || g->places_[position_].has_bomb || g->places_[position_].has_player || g->places_[position_].type_ == hospital || g->places_[position_].type_ == prision) { 
            // 判断loc是否属于[0, 69]
            // 判断loc是否和当前位置差距 > 10
            // 判断loc是否有人、有道具
            // 判断loc是否在医院、监狱
            g->out_tip(CantPlaceBarrier);
            return false;
        }else {
            barrier_ --;
            g->place_tool(loc, TOOL_BARRIER);
            change_map(loc, BARRIER_PIC, COLOR_BASIC);
            return true;
        }
    }
} // 放置障碍
bool Player::query() {
    std::string str;
    int total[4];
    std::string s1 = "您现在拥有如下资产：\n资金：";
    std::string s2 = 
    str = s1 + std::to_string(property_) + "元\n点数：" + credit_ + "点\n固定资产：\n%s\0", , , QueryTitleStr);
    for(int i = 0; i < places_.size(); i ++) {
        char str_pos[50];
        int pos = places_[i];
        int district;
        if (pos < 28){
            district = 1;
        }else if (pos < 35) {
            district = 2;
        }else {
            district = 3;
        }
        int level = g->places_[pos].get_level();
        std::string LandLevel;
        switch (level) {
        case 0:
            LandLevel = LandEmptyStr;
            total[0] ++;
            break;
        case 1:
            LandLevel = LandLevel1Str;
            total[1] ++;
            break;
        case 2:
            LandLevel = LandLevel2Str;
            total[2] ++;
            break;
        case 3:
            LandLevel = LandLevel3Str;
            total[3] ++;
            break;    
        default:
            break;
        }
        sprintf(str_pos, "%d\t%s%d\t%s\n\0", pos, LandTypeStr, district, level);
        str += str_pos;
    }
    init_tips(str,COLOR_BASIC);
    show_tips();
} // 查询财产信息