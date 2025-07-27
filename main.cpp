#include <iostream>
#include <memory>
#include "GlobalMap.h"
#include "GameCharacter.h"
#include "SearchState.h"
#include "GameManager.h"

int main() {
    // GlobalMap& map = GlobalMap::getInstance();
    // map.initializeRandom(20,20);
    //
    // GameCharacter gc;
    //
    // MapView mapView (&gc);
    //
    // while (mapView.getWindow().isOpen()) {
    //     mapView.render();
    // }

    GlobalMap& map = GlobalMap::getInstance();
    map.initializeRandom(50,50);
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
