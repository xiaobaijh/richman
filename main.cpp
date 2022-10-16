#pragma once
#include <string>
#include <iostream>

#include "player.h"
#include "place.h"
#include "map.h"

std::vector<Player> player_lists;
void init_player(int player_num);
void game();

int main() {
    int player_num;
    init_map();
    init_player(player_num);
    while (player_lists.size() != 0) {
        game();
    }
}

void game() {
    //1.遍历玩家list
    //2.遍历玩家拥有的道具询问是否使用
    //3.遍历玩家房产询问是否升级/出卖
    //4.掷骰子
    //5.根据掷完骰子的位置执行不同的特殊功能
    //6.收租，购买等
}