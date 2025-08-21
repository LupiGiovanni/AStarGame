//
// Created by gionimbus on 8/20/25.
//

#include <gtest/gtest.h>
#include "GameCharacter.h"

class GameCharacterTest : public ::testing::Test {
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

TEST_F (GameCharacterTest, ConstructorAndGetters) {
    GameCharacter character (2,3);

    EXPECT_EQ(character.getX(), 2);
    EXPECT_EQ(character.getY(), 3);
}

TEST_F (GameCharacterTest, DefaultContructor) {
    GameCharacter character;

    EXPECT_EQ(character.getX(), 0);
    EXPECT_EQ(character.getY(), 0);
}

TEST_F (GameCharacterTest, FindPathValidTarget) {
    GameCharacter character (0,0);

    //Find path to reachable position
    std::vector<SearchState> path = character.findPath(4, 0);

    EXPECT_FALSE(path.empty()) << "Path should be found to reachable target";

    EXPECT_EQ(path[0].getX(), 0);
    EXPECT_EQ(path[0].getY(), 0);

    EXPECT_EQ(path.back().getX(), 4);
    EXPECT_EQ(path.back().getY(), 0);
}

TEST_F (GameCharacterTest, FindPathToObstacle) {
    GameCharacter character (0,0);

    std::vector<SearchState> path = character.findPath(1,1);

    EXPECT_TRUE(path.empty()) << "No path should be found to obstacle";
}

TEST_F (GameCharacterTest, MoveStepToGoal) {
    GameCharacter character(0, 0);

    std::vector<SearchState> path = character.findPath(3, 3);
    ASSERT_FALSE(path.empty());

    int initialPathSize = path.size();
    int initialX = character.getX();
    int initialY = character.getY();

    character.moveStepToGoal(path);

    EXPECT_EQ( path.size(), initialPathSize - 1 ) << "Path should be shortened by one";
}

class MockObserver : public Observer {
public:
    bool updateCalled = false;

    void update() override { updateCalled = true; }
    void attach() override {}
    void detach() override {}
};

TEST_F(GameCharacterTest, ObserverPattern) {
    GameCharacter character(0, 0);
    MockObserver observer;

    character.subscribe(&observer);

    std::vector<SearchState> path = character.findPath(1, 0);
    ASSERT_FALSE(path.empty());

    observer.updateCalled = false;
    character.moveStepToGoal(path);

    EXPECT_TRUE(observer.updateCalled) << "Observer should be notified on move";
}