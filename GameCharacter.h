//
// Created by gionimbus on 7/21/25.
//

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <list>
#include "Subject.h"
#include "GlobalMap.h"


class GameCharacter: public Subject {
public:
    explicit GameCharacter(const GlobalMap& map):x(0), y(0), map(map) {}
    bool move (int dx, int dy);
    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

private:
    int x;
    int y;
    std::list<Observer*> observers;
    const GlobalMap& map;
};


#endif //GAMECHARACTER_H
