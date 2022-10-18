#pragma once
#include "gsystem.h"
#include "common.h"
#include "display.h"
#include <string>
#include <regex>
#include <algorithm>

using std::cin;
void Gsystem::out_tips(std::string &tip) {
    std::cout << tip << std::endl;
}

void Gsystem::out_err(std::string &tip) {
    std::cerr << tip << std::endl;
}

int Gsystem::parse_input(std::string &input) {
    std::regex player_seq_reg("^[^A-Za-z]*$");
    bool ret = std::regex_match(input, player_seq_reg);
    if (ret) {
        return ORDER_SEQ;
    }
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    if (input == "help") {
        return ORDER_HELP;
    }
    if (input == "roll") {
        return ORDER_ROLL;
    }
    return -1;
}

bool Gsystem::set_user(std::string seq) {
    auto len = seq.length();
    if (len < 2 || len > 4)
        return false;
    //seq 可以是asqj

    for (size_t i = 0; i < len; ++i) {
        if (seq[i] != 'q' || seq[i] != 'a' || seq[i] != 's' || seq[i] != 'j')
            return false;
        if (seq.find(seq[i], i + 1) != seq.npos)
            return false;
    }

    for (auto i : seq) {
        Player temp = Player(i);
        players_.emplace(seq[i], temp);
    }
    if (players_.size() != seq.size()) {
        return false;
    }
    user_order_ = seq;
    user_num_ = len;
    return true;
}

bool Gsystem ::step() {
    for (auto i : user_order_) {
        current_player_ = user_order_[i];
        auto res = player_step(players_[current_player_]);
    }
}

int Gsystem::player_step(Player &player) {
    player_state current_player_state = player.get_state();
    switch (current_player_state) {
    case stop: {
        return 0;
    }
    case bankrupt: {
        return -1; //todo:step返回码还未确定
    }
    }

    if (player.query_use_tool()) {
        //todo 输出系统提示,处理用户输入后调用使用函数
        //use_tool(int loc, int type)
        return false;
    }

    if (!player.query_sell_lands()) {
        return false;
    }

    auto step = get_dices();

    auto position_type = update_position(player, step);
    //更新位置的过程中可能出现：
    //1.玩家遇到炸弹，被传送至医院，返回场地type为hospital
    //2.玩家遇到障碍，被停留在障碍所在处，
    //3.玩家遇到监狱，礼品屋，道具屋，魔法屋，矿地返回场地类型为prison等
    //4.玩家遇到普通地块返回场地类型为
    current_player_state = player.get_state();
    switch (position_type) {
    case hospital: {
        player.hospital();
        break;
    }

    case prision: {
        player.prison();
        break;
    }
    case mine: {
        player.mine();
        break;
    }
    case gift_house: {
        player.gift_ouse();
        break;
    }
    case tool_house: {
        player.tool_house();
        break;
    }
    case common: {
        //player.charge();
        break;
    }
    }
}
