//
// Created by gionimbus on 7/20/25.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GlobalMap.h"

constexpr int reachable = 1;
constexpr int unreachable = 9;
constexpr int error = -1;

GlobalMap::~GlobalMap() {
    delete[] values;
}

int GlobalMap::getValue (int x, int y) const {
    if ( x < 0 || x >= width || y < 0 || y >= height )
        return unreachable;

    if (values == nullptr) {
        std::cout << "Map is not initialized" << std::endl;;
        return error;
    }

    return values[ y * width + x ];
}

GlobalMap& GlobalMap::getInstance() {
    static GlobalMap instance;
    return instance;
}

void GlobalMap::initialize (int map_width, int map_height, const int* map_values) {
    width = map_width;
    height = map_height;
    if (map_values != nullptr) {
        values = new int[ width * height ];
        for (int i = 0; i < width * height; i++)
            values[i] = map_values[i];
        initialized = true;
    }
}

bool GlobalMap::isInitialized () const {
    return initialized;
}