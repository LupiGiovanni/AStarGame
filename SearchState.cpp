//
// Created by gionimbus on 7/20/25.
//

#include <cmath>
#include "GlobalMap.h"
#include "SearchState.h"

constexpr int error = -1;

void SearchState::printStateInfo() const {
    std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
}

float SearchState::GoalDistanceEstimate(SearchState& goal) {
    return std::abs( x - goal.x ) + std::abs( y - goal.y );
}

bool SearchState::IsGoal(SearchState& goal) {
    if ( x == goal.x && y == goal.y )
        return true;
    return false;
}

bool SearchState::GetSuccessors (AStarSearch<SearchState>* astarsearch, SearchState* predecessor) {
    if (predecessor == nullptr || astarsearch == nullptr)
        return false;

    SearchState newState;
    GlobalMap& map = GlobalMap::getInstance();

    if (!map.isInitialized()) {
        std::cout << "Map is not initialized" << std::endl;
        return false;
    }

    if ( (map.getValue(x-1, y) < 9) && !((predecessor->x == x-1) && (predecessor->y == y)) ) {
        newState.x = x-1;
        newState.y = y;
        astarsearch->AddSuccessor(newState);
    }

    if ( (map.getValue(x+1, y) < 9) && !((predecessor->x == x+1) && (predecessor->y == y)) ) {
        newState.x = x+1;
        newState.y = y;
        astarsearch->AddSuccessor(newState);
    }

    if ( (map.getValue(x, y-1) < 9) && !((predecessor->x == x) && (predecessor->y == y-1)) ) {
        newState.x = x;
        newState.y = y-1;
        astarsearch->AddSuccessor(newState);
    }

    if ( (map.getValue(x, y+1) < 9) && !((predecessor->x == x) && (predecessor->y == y+1)) ) {
        newState.x = x;
        newState.y = y+1;
        astarsearch->AddSuccessor(newState);
    }

    return true;
}

float SearchState::GetCost (SearchState& successor) {
    GlobalMap& map = GlobalMap::getInstance();
    if (!map.isInitialized()) {
        std::cout << "Map is not initialized" << std::endl;
        return error;
    }
    return map.getValue(x, y);
}

bool SearchState::IsSameState (SearchState& rhs) {
    if ( x == rhs.x && y == rhs.y )
        return true;
    return false;
}

size_t SearchState::Hash() {
    size_t h1 = hash<float>{}(x);
    size_t h2 = hash<float>{}(y);
    return h1 ^ ( h2 << 1 );
}

