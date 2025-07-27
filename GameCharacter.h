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
    GameCharacter(): x(0), y(0) {}
    int getX() const { return x; }
    int getY() const { return y; }
    bool move (int dx, int dy);
    std::vector<SearchState> findPath (int goalX, int goalY);
    void moveStepToGoal(std::vector<SearchState> &path);

    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

private:
    int x;
    int y;
    std::list<Observer*> observers;
};


#endif //GAMECHARACTER_H
