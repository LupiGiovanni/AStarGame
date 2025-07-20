//
// Created by gionimbus on 7/20/25.
//

#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H
#include "stlastar.h"
#include "GlobalMap.h"


class SearchState {
public:
    SearchState(int px, int py): x(px), y(py) {}
    void printStateInfo();
    int getMapValue (const GlobalMap& map, int x, int y);

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
};



#endif //SEARCHSTATE_H
