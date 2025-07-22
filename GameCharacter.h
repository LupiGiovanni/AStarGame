//
// Created by gionimbus on 7/21/25.
//

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <list>
#include <memory>
#include "SearchState.h"
#include "Subject.h"
#include "GlobalMap.h"


class GameCharacter: public Subject {
public:
    GameCharacter(int x, int y): x(x), y(y) {}
    bool move (int dx, int dy);
    std::vector<SearchState> reachGoal (SearchState& goal);

    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

private:
    int x;
    int y;
    std::list<Observer*> observers;
};


#endif //GAMECHARACTER_H
