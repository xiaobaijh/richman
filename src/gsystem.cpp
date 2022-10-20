#include "gsystem.h"
#include "common.h"
#include "display.h"
#include "place.h"
#include "tips.h"
#include "gutil.h"
#include <cstdlib>
#include <exception>
#include <string>
#include <regex>
#include <algorithm>

using std::cin;

Gsystem::Gsystem() {
}

Gsystem::~Gsystem() {
}
void Gsystem::init_map() {
    int i = 0;
    map_[i++] = 'S';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        map_[i++] = '0';
    }
    places_[i].type_ = hospital;
    map_[i++] = 'H';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        map_[i++] = '0';
    }
    places_[i].type_ = tool_house;
    map_[i++] = 'T';
    for (int m = 0; m < 6; ++m) {
        places_[i].price_ = 500;
        map_[i++] = '0';
    }
    places_[i].type_ = gift_house;
    map_[i++] = 'G';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        map_[i++] = '0';
    }
    places_[i].type_ = prision;
    map_[i++] = 'P';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        map_[i++] = '0';
    }
    places_[i].type_ = magic_house;
    map_[i++] = 'M';
    for (int m = 0; m < 6; ++m) {
        places_[i].price_ = 500;
        map_[i++] = '$';
    }
    init_display();
    display_map(29, 8, map_);
}

bool Gsystem::set_user(std::string &seq, int money) {
    auto len = seq.length();
    if (len < 2 || len > 4)
        return false;
    for (size_t i = 0; i < len; ++i) {
        if (!isPlayerName(seq[i]))
            return false;
        if (seq.find(seq[i], i + 1) != seq.npos)
            return false;
    }
    for (auto i = 0; i < len; i++) {
        players_.emplace(seq[i], Player(seq[i], money));
    }
    user_num_ = players_.size();
    user_order_ = seq;
    return true;
}

void Gsystem::out_tip(std::string tip) {
    // std::cout << tip << std::endl;
    const char *char_tip = tip.c_str();
    print_info(char_tip);
}

void Gsystem::out_help() {
    init_tips(HELPStr,1200);
    show_tips();
}
// todo
std::string Gsystem::convert_input(char actor) {
    std::string hint =get_name(actor)+ "->";
    const char *char_hint = hint.c_str();
    int clour = get_clour(actor);
    get_input(char_hint, clour, input_buffer_, 100);
    std::string result = input_buffer_;
    return result;
}

void Gsystem::out_err(std::string &tip) {
    std::cerr << tip << std::endl;
}

int Gsystem::prarse_input(std::string &input) {
    std::regex pat("\\s*(\\w*)\\s*(.*)");
    std::regex number_pat("\\+?[1-9][0-9]*$");
    std::smatch result;
    if (std::regex_match(input, result, pat)) {
        auto func_name = result.str(1);
        auto cmd = result.str(2);
        func_name = to_lower(func_name);
        if (func_name == "quit") {
            game_over_ = true;
            return ORDER_QUIT;
            // todo quit
        } else if (func_name == "roll") {
            return ORDER_ROLL;
        } else if (func_name == "y") {
            return ORDER_Y;
        } else if (func_name == "n") {
            return ORDER_N;
        } else if (func_name == "robot") {
            return ORDER_ROBOT;
        } else if (func_name == "query") {
            return ORDER_QUERY;
        } else if (func_name == "help") {
            out_help();
            return 0;
        } else if (func_name == "print") {
            // todo print
            return -1;
        } else if ((func_name == "sell") || (func_name == "block") || (func_name == "bomb") || (func_name == "step")) {
            std::smatch result_num;
            if (std::regex_match(cmd, result_num, number_pat)) {
                return std::stoi(cmd);
            }
        } else if (func_name == "preset") {
            if (!preset(cmd)) {
                out_tip(CmdErrorStr);
            }
        }
        return ORDER_WRONG;
    }
}

bool Gsystem::preset(std::string &cmd) {
    std::istringstream is(cmd);
    std::string s;
    std::vector<std::string> paras;
    while (is >> s) {
        paras.push_back(s);
    }
    if (paras[0] == "money") {
        set_property(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "credit") {
        set_credit(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "state") {
        set_state(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "bomb") {
        set_bomb(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "barrier") {
        set_barrier(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "robot") {
        set_robot(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "god") {
        set_god(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "pos") {
        set_user_pos(paras[1][0], std::stoi(paras[2]));
        return true;
    } else if (paras[0] == "building") {
        set_building(std::stoi(paras[1]), std::stoi(paras[2]), paras[3][0]);
        return true;
    } else if (paras[0] == "building-tool") {
        place_tool(paras[1][0], std::stoi(paras[2]));
        return true;
    }
    is.str("");
    return false;
}

bool print() {
    std:: string order = "aqsj";
    

}

bool Gsystem::step() {
    for (auto i =0;i<user_num_;i++) {
        if (user_num_ == 0) {
            return false;
        }
        if (players_[user_order_[i]].isBankruptcy()) {
            continue;
        }
        current_player_ = user_order_[i];
        if (!player_step(current_player_)) {
            return false;
        }
    }
    //更新位置的过程中可能出现：
    // 1.玩家遇到炸弹，被传送至医院，返回场地type为hospital
    // 2.玩家遇到障碍，被停留在障碍所在处，
    // 3.玩家遇到监狱，礼品屋，道具屋，魔法屋，矿地返回场地类型为prison等
    // 4.玩家遇到普通地块返回场地类型为
    auto current_player_state = players_[current_player_].get_state();
    auto current_player_pos = players_[current_player_].get_position();
    auto current_position_type = places_[current_player_pos].type_;
    switch (current_position_type) {
    case hospital: {
        players_[current_player_].got_hospital();
        break;
    }

    case prision: {
        players_[current_player_].got_prison();
        break;
    }
    case mine: {
        players_[current_player_].got_mine();
        break;
    }
    case gift_house: {
        players_[current_player_].got_gift_house();
        break;
    }
    case tool_house: {
        players_[current_player_].got_tool_house();
        break;
    }
    case common: {
        // player.charge();
        break;
    }
    }
    return true;
}
bool Gsystem::player_step(char actor) {
    player_state current_player_state = players_[actor].get_state();
    switch (current_player_state) {
    case stop: {
        return true;
    }
    case bankrupt: {
        return true;
    }
    }

    if (players_[actor].query_use_tool()) {
        // todo 输出是否使用道具信息并获取处理
        // use_tool(int loc, int type)
    }

    if (players_[actor].query_sell_lands()) {
        // todo 输出是否使用买地并获取处理
        // use_tool(int loc, int type)
        //
    }
    // todo 获取掷骰子指令，赋给step
    auto step = get_dices();
    update_position(actor, step);
    return true;
}

bool Gsystem::ready() {
}

int Gsystem::get_dices() {
} //模拟掷骰子
bool Gsystem::use_tool(int loc, int type) {
} //使用道具
place_type Gsystem::update_position(char actor, int position) {
} //根据位置更新玩家信息，考虑地形，
  //在这里修改玩家状态，返回结束后所在地形特征

bool Gsystem::set_current_user(int cur_user) {
} //设置当前玩家
bool Gsystem::set_current_user(char cur_user) {
} //设置当前玩家
int Gsystem::get_current_user(void) {
} //获得当前玩家

bool Gsystem::set_user_pos(char user, int loc) {
    if ((loc < 0) || (loc > 69)) {
        return false;
    }
    return true;
} //设置玩家位置
bool Gsystem::set_property(char user, int num) {
} //设置玩家钱
bool Gsystem::set_credit(char user, int num) {
} //设置玩家点数
bool Gsystem::set_state(char user, int num) {
} //设置玩家停止回合数
bool Gsystem::set_bomb(char user, int num) {
} //设置玩家炸弹数
bool Gsystem::set_barrier(char user, int num) {
} //设置玩家路障数
bool Gsystem::set_robot(char user, int num) {
} //设置玩家机器人数
bool Gsystem::set_god(char user, int num) {
} //设置财神回合
bool Gsystem::set_building(int loc, int level, char owner) {
} //设置建筑物状态
bool Gsystem::place_tool(int loc, int type) {
} //防止道具1炸弹2路障