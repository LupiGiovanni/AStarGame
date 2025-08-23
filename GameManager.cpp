//
// Created by gionimbus on 7/24/25.
//

#include <cmath>
#include "GameManager.h"

GameManager::GameManager(): gc(new GameCharacter()), mapView(new MapView(gc)), currentPath({}) {
    gc->subscribe(mapView);
    movementDelay = sf::milliseconds(150);
}

GameManager::~GameManager() {
    delete gc;
    delete mapView;
}

void GameManager::update (const sf::Event& event) {

    if (event.type == sf::Event::Closed)
      mapView->getWindow().close();

    else if (event.type == sf::Event::MouseButtonPressed) {
        int goalX = transformToMapCoordinateX(event.mouseButton.x);
        int goalY = transformToMapCoordinateY(event.mouseButton.y);

        currentPath = gc->findPath(goalX, goalY);
    }
}

void GameManager::updateMovement() {
    if (!currentPath.empty() && movementClock.getElapsedTime() >= movementDelay) {
        gc->moveStepToGoal(currentPath);
        movementClock.restart();
    }
}

void GameManager::render () {
    mapView->render();
}

int GameManager::transformToMapCoordinateX (int mouseX) const {
    int mapX = static_cast<int> (floor(mouseX / mapView->getTileWidth()));
    return mapX;
}

int GameManager::transformToMapCoordinateY (int mouseY) const {
    int mapY = static_cast<int> (floor(mouseY / mapView->getTileHeight()));
    return mapY;
}

bool GameManager::isRunning() const {
    return mapView->getWindow().isOpen();
}

bool GameManager::pollEvent (sf::Event& event) {
    return mapView->getWindow().pollEvent(event);
}


