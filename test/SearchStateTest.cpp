//
// Created by gionimbus on 8/21/25.
//

#include <gtest/gtest.h>
#include "SearchState.h"

class SearchStateTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup test map
        const int testData[] = { 1, 1, 9,
                                 1, 9, 1,
                                 1, 1, 1 };

        GlobalMap& map = GlobalMap::getInstance();
        map.initialize(3, 3, testData);
    }
};

TEST_F(SearchStateTest, ConstructorAndGetters) {
    SearchState state(2, 3);

    EXPECT_EQ(state.getX(), 2);
    EXPECT_EQ(state.getY(), 3);
}

TEST_F(SearchStateTest, DefaultConstructor) {
    SearchState state;

    EXPECT_EQ(state.getX(), 0);
    EXPECT_EQ(state.getY(), 0);
}

TEST_F(SearchStateTest, ManhattanDistance) {
    SearchState start(0, 0);
    SearchState goal(2, 2);

    float distance = start.GoalDistanceEstimate(goal);

    EXPECT_FLOAT_EQ(distance, 4.0f) << "Manhattan distance should be |2-0| + |2-0| = 4";
}

TEST_F(SearchStateTest, IsGoalTrue) {
    SearchState state(1, 1);
    SearchState goal(1, 1);

    EXPECT_TRUE(state.IsGoal(goal)) << "Same position should be goal";
}

TEST_F(SearchStateTest, IsGoalFalse) {
    SearchState state(0, 0);
    SearchState goal(1, 1);

    EXPECT_FALSE(state.IsGoal(goal)) << "Different position should not be goal";
}

TEST_F(SearchStateTest, IsSameStateTrue) {
    SearchState state1(2, 3);
    SearchState state2(2, 3);

    EXPECT_TRUE(state1.IsSameState(state2)) << "Same coordinates should be same state";
}

TEST_F(SearchStateTest, IsSameStateFalse) {
    SearchState state1(2, 3);
    SearchState state2(3, 2);

    EXPECT_FALSE(state1.IsSameState(state2)) << "Different coordinates should not be same state";
}

TEST_F(SearchStateTest, HashConsistency) {
    SearchState state1(2, 3);
    SearchState state2(2, 3);
    SearchState state3(3, 2);

    EXPECT_EQ(state1.Hash(), state2.Hash()) << "Same states should have same hash";
    EXPECT_NE(state1.Hash(), state3.Hash()) << "Different states should have different hash";
}

TEST_F(SearchStateTest, GetCostReturnsMapValue) {
    SearchState state(0, 0);
    SearchState successor(1, 0);

    float cost = state.GetCost(successor);

    EXPECT_FLOAT_EQ(cost, 1.0f) << "Cost should match map value at current position";
}
