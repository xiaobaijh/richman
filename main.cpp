#pragma once
#include <string>
#include <iostream>

#include "player.h"
#include "place.h"

int main() {
    std::string name = "ddddd";
    Player wjh = Player(name);
    std::cout << wjh.get_name();
    return 0;
}