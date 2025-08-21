//
// Created by gionimbus on 8/20/25.
//

#include <gtest/gtest.h>
#include "GameCharacter.h"

class GameChatacterTest : public ::testing::Test {
protected:
    void SetUp() override {
        const int testData[] = { 1, 1, 1, 1, 1,
                                 1, 9, 9, 9, 1,
                                 1, 1, 1, 1, 1,
                                 1, 9, 9, 1, 1,
                                 1, 1, 1, 1, 1 };

        GlobalMap& map = GlobalMap::getInstance();
        map.initialize(5, 5, testData);
    }
};

TEST_F (GameChatacterTest, ConstructorAndGetters) {
    GameCharacter character (2,3);

    EXPECT_EQ(character.getX(), 2);
    EXPECT_EQ(character.getY(), 3);
}

TEST_F (GameChatacterTest, DefaultContructor) {
    GameCharacter character;

    EXPECT_EQ(character.getX(), 0);
    EXPECT_EQ(character.getY(), 0);
}

TEST_F (GameChatacterTest, FindPathValidTarget) {
    GameCharacter character (0,0);

    //Find path to reachable position
    std::vector<SearchState> path = character.findPath(4, 0);

    EXPECT_FALSE(path.empty()) << "Path should be found to reachable target";

    EXPECT_EQ(path[0].getX(), 0);
    EXPECT_EQ(path[0].getY(), 0);

    EXPECT_EQ(path.back().getX(), 4);
    EXPECT_EQ(path.back().getY(), 0);
}

TEST_F (GameChatacterTest, FindPathToObstacle) {
    GameCharacter character (0,0);

    std::vector<SearchState> path = character.findPath(1,1);

    EXPECT_TRUE(path.empty()) << "No path should be found to obstacle";
}

TEST_F (GameChatacterTest, MoveStepToGoal) {
    GameCharacter character(0, 0);

    std::vector<SearchState> path = character.findPath(2, 0);
    ASSERT_FALSE(path.empty());

    int initialPathSize = path.size();
    int initialX = character.getX();
    int initialY = character.getY();

    character.moveStepToGoal(path);

    EXPECT_EQ(path.size(), initialPathSize - 1) << "Path should be shortened by one";
    EXPECT_TRUE(character.getX() != initialX || character.getY() != initialY) << "Character position should change";
}

