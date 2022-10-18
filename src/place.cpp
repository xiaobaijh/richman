#include "place.h"

Place::~Place() {
}

bool Place::set_state(place_state state) {
    if (state_ != 0) {
        return false;
    }
    state_ = state;
    return true;
}