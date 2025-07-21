//
// Created by gionimbus on 7/21/25.
//

#include "GameCharacter.h"

constexpr int reachable = 1;

bool GameCharacter::move (int dx, int dy) {
    if (map.getValue(x + dx, y + dy) == reachable) {
        x += dx;
        y += dy;
        return true;
    }
    return false;
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

