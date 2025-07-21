//
// Created by gionimbus on 7/20/25.
//

#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H

#include <memory>
#include "stlastar.h"
#include "GlobalMap.h"


class SearchState {
public:
    SearchState(int x, int y, std::shared_ptr<const GlobalMap> map): x(x), y(y), map(map) {}
    void printStateInfo() const;
    int getX () const { return x; }
    int getY () const { return y; }

    //stlastar library requires to implement the following methods
    float GoalDistanceEstimate (SearchState& goal);
    bool IsGoal (SearchState& goal);
    bool GetSuccessors (AStarSearch<SearchState>* astarsearch, SearchState* predecessor);
    float GetCost (SearchState& successor);
    bool IsSameState (SearchState& rhs);
    size_t Hash();

private:
    int x;
    int y;
    std::shared_ptr<const GlobalMap> map;
};


#endif //SEARCHSTATE_H
