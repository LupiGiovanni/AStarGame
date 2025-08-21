
//
// Created by gionimbus on 8/21/25.
//

#include <gtest/gtest.h>
#include "GlobalMap.h"

TEST (GlobalMapTest, SingletonInstance) {
    GlobalMap& map1 = GlobalMap::getInstance();
    GlobalMap& map2 = GlobalMap::getInstance();

    EXPECT_EQ(&map1, &map2) << "GlobalMap should be singleton";
}

TEST (GlobalMapTest, InitializationWithData) {
    const int width = 3;
    const int height = 3;
    const int testData[] = { 1, 1, 9,
                             1, 1, 1,
                             9, 1, 1  };

    GlobalMap& map = GlobalMap::getInstance();
    map.initialize(width, height, testData);

    EXPECT_TRUE(map.isInitialized());
    EXPECT_EQ(map.getWidth(), width);
    EXPECT_EQ(map.getHeight(), height);

    EXPECT_EQ(map.getValue(0, 0), 1);
    EXPECT_EQ(map.getValue(2, 0), 9);
    EXPECT_EQ(map.getValue(0, 2), 9);
}

TEST (GlobalMapTest, RandomInitialization) {
    const int width = 10;
    const int height = 10;

    GlobalMap& map = GlobalMap::getInstance();
    map.initializeRandom(width, height);

    EXPECT_TRUE(map.isInitialized());
    EXPECT_EQ(map.getWidth(), width);
    EXPECT_EQ(map.getHeight(), height);

    EXPECT_EQ(map.getValue(0, 0), 1);

    bool allValid = true;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int value = map.getValue(x, y);
            if (value != 1 && value != 9) {
                allValid = false;
                break;
            }
        }
        if (!allValid) break;
    }

    EXPECT_TRUE(allValid) << "All map values should be 1 or 9";
}

TEST (GlobalMapTest, GetValueOutOfBounds) {
    const int width = 5;
    const int height = 5;

    GlobalMap& map = GlobalMap::getInstance();
    map.initializeRandom(width, height);

    EXPECT_EQ(map.getValue(-1, 0), 9) << "Out of bounds should return unreachable";
    EXPECT_EQ(map.getValue(0, -1), 9) << "Out of bounds should return unreachable";
    EXPECT_EQ(map.getValue(width, 0), 9) << "Out of bounds should return unreachable";
    EXPECT_EQ(map.getValue(0, height), 9) << "Out of bounds should return unreachable";
}