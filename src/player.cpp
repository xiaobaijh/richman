#include "player.h"
#include <string>

Player::~Player() {
    //
}

std::string Player::get_name() {
    return name_;
}