//
// Created by gionimbus on 7/21/25.
//

#include <vector>
#include "GlobalMap.h"
#include "GameCharacter.h"

constexpr int reachable = 1;

bool GameCharacter::move (int dx, int dy) {
    GlobalMap& map = GlobalMap::getInstance();
    if (!map.isInitialized()) {
        std::cout << "Map is not initialized" << std::endl;
        return false;
    }

    if (map.getValue(x + dx, y + dy) == reachable) {
        x += dx;
        y += dy;
        notify();
        return true;
    }
    return false;
}

std::vector<SearchState> GameCharacter::findPath (int goalX, int goalY) {
    SearchState start (x, y);
    SearchState goal (goalX, goalY);
    AStarSearch<SearchState> search;
    search.SetStartAndGoalStates(start, goal);
    unsigned int searchProgress;
    std::vector<SearchState> path;

    do {
        searchProgress = search.SearchStep();
    }
    while (searchProgress == AStarSearch<SearchState>::SEARCH_STATE_SEARCHING);

    if (searchProgress == AStarSearch<SearchState>::SEARCH_STATE_SUCCEEDED) {
        std::cout << "Search succeeded" << std::endl;

        //Saves the path to the goal
        SearchState* state = search.GetSolutionStart();
        while (state != nullptr) {
            path.push_back(*state);
            state = search.GetSolutionNext();
        }
        search.FreeSolutionNodes();
    }
    else if (searchProgress == AStarSearch<SearchState>:: SEARCH_STATE_FAILED)
        std::cout << "Search failed" << std::endl;

    search.EnsureMemoryFreed();
    return path;
}

void GameCharacter::moveStepToGoal (std::vector<SearchState>& path) {
    if (!path.empty()) {
        SearchState nextState = path.front();
        x = nextState.getX();
        y = nextState.getY();
        notify();
        path.erase(path.begin());
    }
}

void GameCharacter::notify() {
    for(auto& observer : observers)
        observer->update();
}

void GameCharacter::subscribe(Observer *o) {
    observers.push_back(o);
}

void GameCharacter::unsubscribe(Observer *o) {
    observers.remove(o);
}

