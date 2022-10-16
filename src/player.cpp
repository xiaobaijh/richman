#include <string>
#include <random>
#include "player.h"

const int map_size = 70;

Player::~Player() {
    //
}

int Player::get_dices() {
    int min = 1, max = 6;
    std::random_device seed;                           //硬件生成随机数种子
    std::ranlux48 engine(seed());                      //利用种子生成随机数引擎
    std::uniform_int_distribution<> distrib(min, max); //设置随机数范围，并为均匀分布
    int random = distrib(engine);                      //随机数
    return random;
}

void Player::update_poistion(int &num) {
    position_ = (position_ += num) % map_size;
}