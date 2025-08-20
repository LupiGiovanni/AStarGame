#include "GlobalMap.h"
#include "GameManager.h"

int main() {
    GlobalMap& map = GlobalMap::getInstance();
    map.initializeRandom(40, 40);
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

//to do: scritte su terminale che indicano bene gli eventi, rimpiazzare i raw pointer
