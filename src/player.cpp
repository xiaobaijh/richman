#pragma once
#include <string>
#include <random>
#include "player.h"
#include "common.h"

bool Player::query_use_tool() {
    if (bomb_ > 0 || barrier_ > 0 || robot_ > 0) {
        return true;
    }
    return false;
}

bool Player::increase_credit() {
    credit_ += GIFT_CREDIT;
    return true;
}

int Player::get_credit() {
    return credit_;
}