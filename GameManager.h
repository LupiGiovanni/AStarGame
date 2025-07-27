//
// Created by gionimbus on 7/24/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GlobalMap.h"
#include "GameCharacter.h"
#include "MapView.h"

class GameManager {
public:
    GameManager(): gc(new GameCharacter()), mapView(new MapView(gc)), currentPath({}) {
        gc->subscribe(mapView);
        movementDelay = sf::milliseconds(150);
    };
    ~GameManager();

    void update (const sf::Event& event);
    void updateMovement();
    void render();
    int transformToMapCoordinateX (int mouseX) const;
    int transformToMapCoordinateY (int mouseY) const;
    bool isRunning() const;
    bool pollEvent(sf::Event& event);

private:
    GameCharacter* gc;
    MapView* mapView;
    std::vector<SearchState> currentPath;
    sf::Clock movementClock;
    sf::Time movementDelay;
};



#endif //GAMEMANAGER_H
