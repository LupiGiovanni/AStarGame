
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