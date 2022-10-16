#pragma once
#include <memory>
#include <valarray>
#include "place.h"

extern const int map_size = 70;
std::valarray<std::unique_ptr<Base>> map[map_size];
char map_colour[map_size];

void init_map() {
    //todo
}