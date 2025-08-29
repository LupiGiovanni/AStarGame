//
// Created by gionimbus on 7/20/25.
//

#include <cstdlib>
#include <ctime>
#include <random>
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

void GlobalMap::initialize (int mapWidth, int mapHeight, const int* mapValues) {
    width = mapWidth;
    height = mapHeight;
    if (mapValues != nullptr) {
        values = new int[ width * height ];
        for (int i = 0; i < width * height; i++)
            values[i] = mapValues[i];
        initialized = true;
    }
}

void GlobalMap::initializeRandom(int mapWidth, int mapHeight) {
    width = mapWidth;
    height = mapHeight;

    values = new int [width * height];

    std::mt19937 rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 100);

    for (int i = 1; i < width * height; i++) {
        values[i] = (dist(rng) < 70) ? reachable : unreachable; // 70% chance for reachable terrain
    }

    //starting point must always be reachable
    values [0] = reachable;

    //creates a safe starting zone for the character to prevent from being blocked at the beginning
    int safeRadius = 4;
    for (int y = 0; y < safeRadius && y < height; y++) {
        for (int x = 0; x < safeRadius && x < width; x++) {
            if (dist(rng) < 85) {
                values[y * width + x] = reachable;
            }
        }
    }

    initialized = true;
}


bool GlobalMap::isInitialized () const {
    return initialized;
}