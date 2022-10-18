#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <regex>

#include "player.h"
#include "place.h"
#include "gsystem.h"

void init_player(int player_num);
void game();

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    // Gsystem sys;
    // std::string line;
    // std::string out;
    // int player_num = 0;
    // int default_fund = 0;
    // while (!sys.Ready()) {
    //     cout << "欢迎进入大富翁游戏！" << endl;
    //     cout << "您可以选择的游戏指令:" << endl
    //          << "help-> 游戏帮助" << endl
    //          << "roll->前进" << endl
    //          << "quit->强制退出" << endl;
    //     out = "请设置玩家初始资金";
    //     sys.out_tips(out);
    //     std::getline(cin, line);
    //     auto res = sys.parse_input(line);
    //     if (res == -1) {
    //         std::stringstream ss(line);
    //         default_fund = 0;
    //         ss >> default_fund;
    //         if (default_fund >= 1000 && default_fund <= 50000) {
    //             sys.set_default_fund(default_fund);
    //             break;
    //         }
    //     }
    // }
    // //sys.out_tips("请选择2~3位不同的不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3.孙小美；4、金贝贝：");
    // while (!sys.Ready()) {
    //     std::getline(cin, line);
    //     auto res = sys.parse_input(line);
    //     if (res == ORDER_SEQ) {
    //         for (auto &e : line) {
    //             if (e == '1')
    //                 e = 'Q';
    //             if (e == '2')
    //                 e = 'A';
    //             if (e == '3')
    //                 e = 'S';
    //             if (e == '4')
    //                 e = 'J';
    //         }
    //         if (sys.set_user(line))
    //             break;
    //     }
    // }

    // while (1) {
    //     sys.step();
    // }

    return 0;
    
}
