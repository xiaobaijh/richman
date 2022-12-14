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
    places_[i].type_ = park;
    places_[i].default_symbol_ = 'S';
    places_[i].has_player = user_num_;
    places_[i].color_ = COLOR_SPECIAL;
    map_[i++] = 'S';
    for (int m = 0; m < 13; ++m) {
        places_[i].base_price_ = 200;
        places_[i].price_ = 200;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = park;
    places_[i].default_symbol_ = 'P';
    places_[i].color_ = COLOR_SPECIAL;
    map_[i++] = 'P';

    for (int m = 0; m < 13; ++m) {
        places_[i].base_price_ = 200;
        places_[i].price_ = 200;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = tool_house;
    places_[i].default_symbol_ = 'T';
    places_[i].color_ = COLOR_SPECIAL;
    map_[i++] = 'T';

    for (int m = 0; m < 6; ++m) {
        places_[i].base_price_ = 500;
        places_[i].price_ = 500;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = gift_house;
    places_[i].default_symbol_ = 'G';
    places_[i].color_ = COLOR_SPECIAL;
    map_[i++] = 'G';

    for (int m = 0; m < 13; ++m) {
        places_[i].base_price_ = 300;
        places_[i].price_ = 300;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = park;
    places_[i].default_symbol_ = 'P';
    places_[i].color_ = COLOR_SPECIAL;
    map_[i++] = 'P';

    for (int m = 0; m < 13; ++m) {
        places_[i].base_price_ = 300;
        places_[i].price_ = 300;
        places_[i].default_symbol_ = '0';
        map_[i++] = '0';
    }
    places_[i].type_ = magic_house;
    places_[i].default_symbol_ = 'M';
    places_[i].color_ = COLOR_SPECIAL;
    map_[i++] = 'M';

    for (int m = 0; m < 6; ++m) {
        places_[i].type_ = mine;
        // places_[i].price_ = 500;
        places_[i].default_symbol_ = '$';
        places_[i].color_ = COLOR_SPECIAL;
        map_[i++] = '$';
    }
    init_display();
    display_map(29, 8, map_);
    init_tips(HELPStr, COLOR_BASIC);
}

bool Gsystem::update_map() {
    for (int i = 0; i < 70; i++) {
        if (places_[i].has_player == 0 && places_[i].has_barrier == false) {
            change_map(i, places_[i].default_symbol_, places_[i].color_);
        }
    }
    return true;
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
    std::regex number_pat("-?(\\d+|\\d+\\.\\d+)[ ]*");
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
            } else if (func_name == "sell") {
                players_[current_player_].sell_land(number);
                return 0;
            } else if (func_name == "block") {
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
        place_tool(std::stoi(paras[1]), std::stoi(paras[2]));
        return true;
    }
    is.str("");
    return false;
}

bool Gsystem::print() {
    int num = user_order_.size();
    int index = 0;
    for (auto ch : user_order_) {
        if (ch == current_player_) break;
        index++;
    }
    printf("\n\nseq ");
    for (int i = 0; i < num; ++i) {
        if (user_order_[(index + i) % num] == '0') {
            continue;
        }
        printf("%c", user_order_[(index + i) % num]);
    }
    printf("\n");
    for (auto ch : "QASJ") {
        if (players_.count(ch) <= 0) continue;
        auto &player = players_[ch];
        if (players_[ch].get_property() < 0) continue;
        printf("%c %d %d %d %d %d %d %d %d\n", ch, player.get_position(), player.get_property(), player.get_credit(),
               players_[ch].get_stop_time(), 0, players_[ch].get_barrier(), player.get_robot(), player.get_god());
    }

    for (int i = 0; i < 70; i++) {
        if (places_[i].level_ == 0 && places_[i].state_ == unowned && (!places_[i].has_barrier)) continue;
        printf("building %d %d %c ", i, places_[i].level_, places_[i].owner_);
        if (places_[i].has_barrier) {
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
        // if (user_num_ == 1) {
        //     out_tip(get_name(user_order_[i]) + WinStr);
        //     return false;
        // }
        if (players_[user_order_[i]].isBankruptcy()) {
            continue;
        }
        current_player_ = user_order_[i];

        if (players_[current_player_].state_ == stop) {
            if (places_[players_[current_player_].get_position()].has_player == 1) {
                change_map(players_[current_player_].get_position(), current_player_, get_clour(current_player_));
            }
            players_[current_player_].stopped();
            continue;
        }
        //???????????????????????????????????????????????????????????????????????????????????????
        auto step = player_step(current_player_);
        if (step < 0 || step > 10000) {
            return false;
        }

        //?????????????????????????????????
        if (!update_position(current_player_, step)) {
            return false;
        }

        //?????????????????????????????????
        auto pos = players_[current_player_].get_position();
        change_map(pos, current_player_, get_clour(current_player_)); //?????????????????????
        update_map();
        auto current_pos_type = places_[pos].type_;
        switch (current_pos_type) {
        case park: {
            break;
        }
        case start: {
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
        case magic_house: {
            players_[current_player_].got_magic_house();
            break;
        }
        default: {
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
        }
        if (players_[current_player_].get_god() > 0) {
            players_[current_player_].decrease_god();
        }
    }
    //???????????????????????????????????????
    // 1.??????????????????????????????????????????????????????type???hospital
    // 2.???????????????????????????????????????????????????
    // 3.????????????????????????????????????????????????????????????????????????????????????prison???
    // 4.?????????????????????????????????????????????
    return true;
}

int Gsystem::player_step(char actor) {
    std::string input;
    int step = 0;
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
        } else if (result > 0 && result < 1000) {
            step = result;
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
    // change_map(pos, places_[pos].default_symbol_, get_clour(places_[pos].owner_)); //??????????????????????????????
    if (places_[pos].has_player != 0) {
        places_[pos].has_player--;
    }
    for (auto i = pos; i <= pos + step; i++) {
        auto tmp = i % 70;
        if (places_[tmp].has_barrier) {
            places_[tmp].has_player++;
            places_[tmp].has_barrier = false;
            change_map(tmp, places_[tmp].default_symbol_, COLOR_SPECIAL);
            players_[actor].set_pos(tmp);
            return true;
        }
    }
    players_[actor].update_poistion(step);
    pos = players_[actor].get_position();
    places_[pos].has_player++;
    return true;
} //?????????????????????????????????????????????

bool Gsystem::ready() {
    return game_over_;
}

//???????????????
int Gsystem::get_dices() {
    int min = 1, max = 6;
    std::random_device seed;                           //???????????????????????????
    std::ranlux48 engine(seed());                      //?????????????????????????????????
    std::uniform_int_distribution<> distrib(min, max); //??????????????????????????????????????????
    return distrib(engine);                            //?????????
}

//????????????
bool Gsystem::use_tool(int loc, int type) {
}

//??????????????????
bool Gsystem::set_current_user(char cur_user) {
    current_player_ = toupper(cur_user);
    // players_[current_player_]=cur_user;
    return true;
}

//??????????????????
bool Gsystem::set_user_pos(char user, int loc) {
    if ((loc < 0) || (loc > 69)) {
        return false;
    }
    players_[user].set_pos(loc);
    places_[loc].has_player += 1;
    return true;
}

//???????????????
bool Gsystem::set_property(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_property(num);
    return true;
}

//??????????????????
bool Gsystem::set_credit(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_credit(num);
    return true;
}

//???????????????????????????
bool Gsystem::set_state(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_stop_time_(num);
    return true;
}

//?????????????????????
bool Gsystem::set_barrier(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_barrier(num);
    return true;
}

//????????????????????????
bool Gsystem::set_robot(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_robot(num);
    return true;
}

//??????????????????
bool Gsystem::set_god(char user, int num) {
    user = toupper(user);
    if (!isPlayerName(user))
        return false;
    players_[user].set_god(num);
    return true;
}

//?????????????????????
bool Gsystem::set_building(int loc, int level, char owner) {
    places_[loc].level_ = level;
    if (level != 0) {
        places_[loc].price_ *= (level + 1);
    }
    places_[loc].state_ = owned;
    places_[loc].owner_ = toupper(owner);
    players_[owner].increase_land(loc);
    return false;
}

//????????????1??????2??????
bool Gsystem::place_tool(int loc, int type) {
    if (loc < 0 || loc >= 70)
        return false;
    if (type == 2) {
        Place &place = places_[loc];
        if (!place.has_barrier)
            place.has_barrier = true;
        return true;
    }
    return true;
}