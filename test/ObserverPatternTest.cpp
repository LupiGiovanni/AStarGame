//
// Created by gionimbus on 8/21/25.
//

#include <gtest/gtest.h>
#include "Observer.h"
#include "GameCharacter.h"

class TestableObserver : public Observer {
public:
    int updateCount = 0;
    bool attachCalled = false;
    bool detachCalled = false;

    void update() override { updateCount++; }
    void attach() override { attachCalled = true; }
    void detach() override { detachCalled = true; }
};

class ObserverPatternTest : public ::testing::Test {
protected:
    void SetUp() override {
        const int testData[] = {1, 1, 1,
                               1, 1, 1,
                               1, 1, 1};

        GlobalMap& map = GlobalMap::getInstance();
        map.initialize(3, 3, testData);
    }
};

TEST_F(ObserverPatternTest, SubscribeAndNotify) {
    GameCharacter character(0, 0);
    TestableObserver observer;

    character.subscribe(&observer);
    character.notify();

    EXPECT_EQ(observer.updateCount, 1) << "Observer should receive one update notification";
}

TEST_F(ObserverPatternTest, MultipleObservers) {
    GameCharacter character(0, 0);
    TestableObserver observer1, observer2;

    character.subscribe(&observer1);
    character.subscribe(&observer2);
    character.notify();

    EXPECT_EQ(observer1.updateCount, 1) << "First observer should receive notification";
    EXPECT_EQ(observer2.updateCount, 1) << "Second observer should receive notification";
}

TEST_F(ObserverPatternTest, UnsubscribeObserver) {
    GameCharacter character(0, 0);
    TestableObserver observer;

    character.subscribe(&observer);
    character.unsubscribe(&observer);
    character.notify();

    EXPECT_EQ(observer.updateCount, 0) << "Unsubscribed observer should not receive notifications";
}

TEST_F(ObserverPatternTest, MoveNotifiesObservers) {
    GameCharacter character(0, 0);
    TestableObserver observer;

    character.subscribe(&observer);

    auto path = character.findPath(1, 0);
    ASSERT_FALSE(path.empty());

    observer.updateCount = 0;
    character.moveStepToGoal(path);

    EXPECT_GT(observer.updateCount, 0) << "Move should trigger observer notification";
}