#pragma once
#include <valarray>
#include "place.h"

const int map_size;
std ::valarray<Place> map[map_size];

void init_map(std::valarray<Place> &map);