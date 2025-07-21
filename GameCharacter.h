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
    GameCharacter(int x, int y, std::shared_ptr<const GlobalMap> map): x(x), y(y), map(map) {}
    bool move (int dx, int dy);
    std::vector<SearchState> reachGoal (SearchState& goal);

    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

private:
    int x;
    int y;
    std::list<Observer*> observers;
    std::shared_ptr<const GlobalMap> map;
};


#endif //GAMECHARACTER_H
