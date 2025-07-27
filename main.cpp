#include <iostream>
#include <memory>
#include "GlobalMap.h"
#include "GameCharacter.h"
#include "SearchState.h"
#include "GameManager.h"

int main() {
    GlobalMap& map = GlobalMap::getInstance();
    map.initializeRandom(25,25);
    GameManager game;
    while (game.isRunning()) {
        sf::Event event;
        game.pollEvent(event);
        game.update(event);
        game.updateMovement();
        game.render();
    }

    return 0;
}

//to do: texture alla mappa, scritte su terminale che indincano bene gli eventi via via che accadono
