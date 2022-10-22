#include "gsystem.h"
#include "common.h"
#include "display.h"
#include "place.h"
#include "tips.h"
#include "gutil.h"
#include "player.h"
#include <cstdlib>
#include <exception>
#include <string>
#include <regex>
#include <algorithm>
#include <random>
#include <unistd.h>

using std::cin;

Gsystem::Gsystem() {
}

Gsystem::~Gsystem() {
}
void Gsystem::init_game_display() {
    int i = 0;
    places_[i].default_symbol_ = 'S';
    map_[i++] = 'S';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = hospital;
    places_[i].default_symbol_ = 'H';
    map_[i++] = 'H';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = tool_house;
    places_[i].default_symbol_ = 'T';
    map_[i++] = 'T';
    for (int m = 0; m < 6; ++m) {
        places_[i].price_ = 500;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = gift_house;
    places_[i].default_symbol_ = 'G';
    map_[i++] = 'G';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = prision;
    places_[i].default_symbol_ = 'P';
    map_[i++] = 'P';
    for (int m = 0; m < 13; ++m) {
        places_[i].price_ = 200;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = magic_house;
    places_[i].default_symbol_ = 'M';
    map_[i++] = 'M';
    for (int m = 0; m < 6; ++m) {
        places_[i].price_ = 500;
        places_[i].default_symbol_ = '$';
        map_[i++] = '$';
    }
    init_display();
    display_map(29, 8, map_);
    init_tips(HELPStr, COLOR_BASIC);
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
        players_[seq[i]].init(this);
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
    show_tips();
}
// todo
std::string Gsystem::convert_input(char actor, int len) {
    std::string hint = get_name(actor) + "->";
    const char *char_hint = hint.c_str();
    int clour = get_clour(actor);
    get_input(char_hint, clour, input_buffer_, len + 1);
    std::string result = input_buffer_;
    return result;
}

void Gsystem::out_err(std::string &tip) {
    std::cerr << tip << std::endl;
}

bool Gsystem::prarse_preset(std::string input) {
    std::regex pat("\\s*(\\w*)\\s*(.*)");
    std::regex number_pat("\\+?[1-9][0-9]*$");
    std::smatch result;
    std::smatch result_num;
    if (std::regex_match(input, result, pat)) {
        auto func_name = result.str(1);
        auto cmd = result.str(2);
        func_name = to_lower(func_name);
        if (func_name != "preset") {
            return false;
        }
        return preset(cmd);
    }
    return false;
}

int Gsystem::prarse_input(std::string &input) {
    if (input == "0") {
        return 0;
    }
    std::regex pat("\\s*(\\w*)\\s*(.*)");
    std::regex number_pat("\\+?[1-9][0-9]*$");
    std::smatch result;
    std::smatch result_num;
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
        } else if (func_name == "robot") {
            players_[current_player_].user_robot();
            return 0;
        } else if (func_name == "query") {
            players_[current_player_].query();
            return ORDER_QUERY;
        } else if (func_name == "help") {
            out_help();
            return 0;
        } else if (func_name == "print") {
            print();
            return 0;
        } else if ((std::regex_match(cmd, result_num, number_pat))) {
            auto number = std::stoi(cmd);
            if (func_name == "step") {
                return number;
            } else if (func_name == "bomb") {
                players_[current_player_].user_bomb(number);
                return 0;
            } else if (func_name == "sell") {
                players_[current_player_].sell_land(number);
                return 0;
            } else if (func_name == "bolck") {
                players_[current_player_].use_barrier(number);
                return 0;
            }
        }
    }
    return ORDER_WRONG;
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

bool Gsystem::print() {
    for (auto ch : user_order_) {
        auto &player = players_[ch];
        if (players_[ch].get_state() == bankrupt) continue;
        printf("%c %d %d %d %d %d %d %d %d\n", ch, player.get_position(), player.get_property(), player.get_credit(), players_[ch].get_state(), players_[ch].get_bomb(), players_[ch].get_barrier(), player.get_robot(), player.get_god());
    }
    int i = -1;
    for (auto &place : places_) {
        ++i;
        if (place.level_ == 0 && place.state_ == unowned) continue;
        printf("building %d %d %c ", i, place.level_, place.owner_);
        if (place.has_bomb) {
            printf("1\n");
        } else if (place.has_barrier) {
            printf("2\n");
        } else {
            printf("0\n");
        }
    }
    return true;
}

bool Gsystem::step() {
    if (user_num_ <= 0) {
        game_over_ = true;
        return false;
    }
    for (auto i = 0; i < user_num_; i++) {
        if (user_num_ == 0) {
            return false;
        }
        if (players_[user_order_[i]].isBankruptcy()) {
            continue;
        }
        current_player_ = user_order_[i];
        //玩家回合一步，处理玩家需要输入的指令，处理完后进入系统回合
        auto step = player_step(current_player_);
        if (step < 0 || step > 100) {
            return false;
        }

        //掷完骰子后更新玩家位置
        if (places_[current_player_].has_player != 0) {
            places_[current_player_].has_player--;
        }

        if (!update_position(current_player_, step)) {
            return false;
        }

        //更新后根据当前位置行动
        auto pos = players_[current_player_].get_position();
        auto current_pos_type = places_[pos].type_;
        change_map(pos, current_player_, get_clour(current_player_)); //移动后改变地图
        switch (current_pos_type) {
        case prision: {
            players_[current_player_].got_prison();
            return true;
        }
        case mine: {
            players_[current_player_].got_mine();
            return true;
        }
        case gift_house: {
            players_[current_player_].got_gift_house();
            return true;
        }
        case tool_house: {
            players_[current_player_].got_tool_house();
            return true;
        }
        case magic_house: {
            // player.magic
            return true;
        }
        }
        auto current_pos_state = places_[pos].state_;
        switch (current_pos_state) {
        case unowned:
            players_[current_player_].buy_land();
            break;
        case owned: {
            if (places_[pos].owner_ == current_player_) {
                players_[current_player_].update_land();
            } else {
                players_[current_player_].charge(places_[pos].owner_);
            }
        }
        }
    }
    //更新位置的过程中可能出现：
    // 1.玩家遇到炸弹，被传送至医院，返回场地type为hospital
    // 2.玩家遇到障碍，被停留在障碍所在处，
    // 3.玩家遇到监狱，礼品屋，道具屋，魔法屋，矿地返回场地类型为prison等
    // 4.玩家遇到普通地块返回场地类型为
    return true;
}

int Gsystem::player_step(char actor) {
    std::string input;
    int step = 0;
    player_state current_player_state = players_[actor].get_state();
    switch (current_player_state) {
    case stop: {
        players_[actor].stopped();
        return 0;
    }
    case bankrupt: {
        return 0;
    }
    }
    out_tip(get_name(actor) + ActorTip);
    input = convert_input(actor, 100);
    while (1) {
        auto result = prarse_input(input);
        if (result == ORDER_ROLL) {
            step = get_dices();
            break;
        } else if (result == ORDER_QUIT) {
            return -1;
        } else if (result == ORDER_WRONG) {
            out_tip(CmdErrorStr);
        } else if (result > 0 && result < 69) {
            step = (prarse_input(input));
            break;
        }
        input = convert_input(actor, 100);
    }
    out_tip(RollStr + std::to_string(step));
    get_input(0, 0, 0, 0);
    return step;
}

bool Gsystem::update_position(char actor, int step) {
    int pos = players_[actor].get_position();
    change_map(pos, places_[pos].default_symbol_, get_clour(places_[pos].owner_)); //在玩家移动前恢复地图
    places_[pos].has_player--;
    for (auto i = pos + 1; i <= pos + step; i++) {
        if (places_[i].has_bomb) {
            places_[i].has_bomb = false;
            places_[i].has_player++;
            players_[actor].got_hospital();
            return true;
        }
        if (places_[i].has_barrier) {
            places_[i].has_bomb = false;
            places_[i].has_player++;
            players_[actor].set_pos(i);
            return true;
        }
    }
    players_[actor].update_poistion(step);
    return true;
} //根据位置更新玩家信息，考虑地形

bool Gsystem::ready() {
    return game_over_;
}

//模拟掷骰子
int Gsystem::get_dices() {
    int min = 1, max = 6;
    std::random_device seed;                           //硬件生成随机数种子
    std::ranlux48 engine(seed());                      //利用种子生成随机数引擎
    std::uniform_int_distribution<> distrib(min, max); //设置随机数范围，并为均匀分布
    return distrib(engine);                            //随机数
}

//使用道具
bool Gsystem::use_tool(int loc, int type) {
}

//设置当前玩家
bool Gsystem::set_current_user(char cur_user) {
    current_player_ = toupper(cur_user);
    // players_[current_player_]=cur_user;
    return true;
}

//设置玩家位置
bool Gsystem::set_user_pos(char user, int loc) {
    if ((loc < 0) || (loc > 69)) {
        return false;
    }
    players_[user].set_pos(loc);
    return true;
}

//设置玩家钱
bool Gsystem::set_property(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_property(num);
    return true;
}

//设置玩家点数
bool Gsystem::set_credit(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_credit(num);
    return true;
}

//设置玩家停止回合数
bool Gsystem::set_state(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_stop_time_(num);
    return true;
}

//设置玩家炸弹数
bool Gsystem::set_bomb(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_bomb(num);
    return true;
}

//设置玩家路障数
bool Gsystem::set_barrier(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_barrier(num);
    return true;
}

//设置玩家机器人数
bool Gsystem::set_robot(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_barrier(num);
    return true;
}

//设置财神回合
bool Gsystem::set_god(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_god(num);
    return true;
}

//设置建筑物状态
bool Gsystem::set_building(int loc, int level, char owner) {
    places_[loc].level_ = level;
    places_[loc].owner_ = toupper(owner);
}

//放置道具1炸弹2路障
bool Gsystem::place_tool(int loc, int type) {
    if (loc < 0 || loc >= 70)
        return false;
    if (type == 2) {
        Place &place = places_[loc];
        if (place.has_barrier)
            place.has_barrier = true;
        return true;
    }
    if (type == 1) {
        Place &place = places_[loc];
        if (place.has_bomb)
            place.has_bomb = true;
        return true;
    }
    return true;
}