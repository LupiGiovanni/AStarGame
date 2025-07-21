//
// Created by gionimbus on 7/20/25.
//

#include <cstdlib>
#include <ctime>
#include "GlobalMap.h"

constexpr int reachable = 1;
constexpr int unreachable = 9;

GlobalMap::GlobalMap(int width, int height) {
    this->width = width;
    this->height = height;

    //Sets random values for the map
    std::srand(std::time(nullptr));
    values = new int[ width * height ];
    for (int i = 0; i < width * height; i++) {
        int random = rand()%2;
        if (random == 0)
            values[i] = reachable;
        else
            values[i] = unreachable;
    }
}

GlobalMap::GlobalMap(int width, int height, const int* values) {
    this->width = width;
    this->height = height;
    this->values = new int[ width * height ];
    for (int i = 0; i < width * height; i++)
        (this->values)[i] = values [i];
}

GlobalMap::~GlobalMap() {
    delete[] values;
}

int GlobalMap::getValue (int x, int y) const {
    if ( x < 0 || x >= width || y < 0 || y >= height )
        return unreachable;

    return values[ y * width + x ];
}