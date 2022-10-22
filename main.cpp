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
#include "display.h"

void init_player(int player_num);
void game();

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
bool test_get_input(Gsystem *g);

int main(int argc, char **argv) {
    Gsystem sys = Gsystem();
    sys.init_game_display();
    // test_get_input(&sys);

    int player_num = 0;
    int default_fund = 1000;
    std::string order = "qasj";
    std::string input;

    while (1) {
        sys.out_tip(InitFundTip);
        input = sys.convert_input('0', 6);
        if (std::stoi(input) <= 50000 && std::stoi(input) >= 1000) {
            default_fund = std::stoi(input);
            break;
        }
    }

    while (1) {
        sys.out_tip(ChoosePlayerTip);
        input = sys.convert_input('0', 10);
        for (auto &e : input) {
            if (e == '1')
                e = 'Q';
            if (e == '2')
                e = 'A';
            if (e == '3')
                e = 'S';
            if (e == '4')
                e = 'J';
        }
        if (sys.set_user(input, default_fund)) {
            clean_info();
            break;
        }
    }
    
    input = sys.convert_input(0, 40);

    while (sys.prarse_preset(input)) {
        input = sys.convert_input( 0,40);

        sys.prarse_preset(input);
    }

    while (sys.step()) {
        ;
    }
    end_display();
    return 0;
}

//需要测试自己的函数可以在加test_xxx函数，在main里调用，单测好烦人
bool test_get_input(Gsystem *g) {
    std::string input;
    std::string order = "qasj";
    g->set_user(order, 5000);
    g->out_tip(CmdErrorStr);              //需要向玩家输入信息时使用，在tips.h下有string，直接传进去即可
    input = g->convert_input('j', 10);    //参数为aqsj之一，代表4个玩家之一，为了显示箭头
    auto result = g->prarse_input(input); //解析指令，有第二个参数的返回大于零的数字，仍需进一步判断，返回-8代表非法指令
    std::cout << result << endl;
    switch (result) {
    case ORDER_HELP: {
        std::cout << "输入了help" << endl;
        break;
    }
    case ORDER_QUERY: {
        std::cout << "输入了query" << endl;
        break;
    }
    case ORDER_ROLL: {
        std::cout << "输入了roll" << endl;
        break;
    }
    case ORDER_Y: {
        std::cout << "输入了y" << endl;
        break;
    } //省略了,不想写了5555
    }
    g->out_tip(CmdErrorStr);
    return true;
}
