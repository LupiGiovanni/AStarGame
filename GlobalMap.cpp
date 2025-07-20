//
// Created by gionimbus on 7/20/25.
//

#include "GlobalMap.h"

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
        return 9;

    return values[ y * width + x ];
}