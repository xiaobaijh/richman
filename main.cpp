#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <regex>

#include "player.h"
#include "place.h"
#include "gsystem.h"
#include "gutil.h"
#include "tips.h"
#include "common.h"

void init_player(int player_num);
void game();

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    Gsystem sys = Gsystem();
    std::string input;
    sys.init_map();

    int player_num = 0;
    int default_fund = 1000;
    std::string order = "1234";

    sys.out_tip(InitFundTip);
    input = sys.convert_input('0', 300);
    if (std::stoi(input) < 50000 && std::stoi(input) > 1000) {
        default_fund = std::stoi(input);
    }

    while (1) {
        sys.out_tip(InitFundTip);
        input = sys.convert_input('0', 300);
        if (std::stoi(input) < 50000 && std::stoi(input) > 1000) {
            default_fund = std::stoi(input);
            break;
        }
    }

    while (1) {
        sys.out_tip(ChoosePlayerTip);
        input = sys.convert_input('0', 30);
        for (auto &e : input) {
            if (e == '1')
                e = 'a';
            if (e == '2')
                e = 'q';
            if (e == '3')
                e = 's';
            if (e == '4')
                e = 'j';
        }
        if (sys.set_user(input, default_fund))
            break;
    }
    while (sys.step()) {
        ;
    }

    while (true) {
        std::getline(cin, input);
        sys.prarse_input(input);
    }
    return 0;
}
