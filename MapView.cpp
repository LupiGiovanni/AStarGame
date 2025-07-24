//
// Created by gionimbus on 7/23/25.
//

#include "MapView.h"

constexpr int windowWidth= 800;
constexpr int windowHeight = 800;
constexpr float delta = 5.0;

MapView::MapView(GameCharacter *gameCharacter): subject(gameCharacter) {
    GlobalMap& map = GlobalMap::getInstance();
    window.create( sf::VideoMode(windowWidth, windowHeight), "A* Game", sf::Style::Close | sf::Style::Titlebar );
}

void MapView::update() override {
    subjectX = subject->getX();
    subjectY = subject->getY();
}

void MapView::attach() override {
    subject->subscribe(this);
}

void MapView::detach() override {
    subject->unsubscribe(this);
}

void MapView::draw() {
    const GlobalMap& map = GlobalMap::getInstance();

    //draws map tiles
    std::vector<std::vector<sf::RectangleShape>> mapTiles (map.getHeight(), std::vector<sf::RectangleShape> (map.getWidth()));
    float tileWidth = ( static_cast<float>(windowWidth) / map.getWidth() );
    float tileHeight = ( static_cast<float>(windowHeight) / map.getHeight() );
    sf::Vector2f tileSize (tileHeight, tileWidth);

    for (int y = 0; y < map.getHeight(); y++)
        for (int x = 0; x < map.getWidth(); x++) {
            mapTiles[y][x].setSize(tileSize);
            mapTiles[y][x].setPosition( (x * tileWidth), (y * tileHeight) );
            if (map.getValue(x, y) == 9) {
                mapTiles[y][x].setFillColor(sf::Color::Black);
                mapTiles[y][x].setOutlineThickness(1);
                mapTiles[y][x].setOutlineColor(sf::Color::White);
            } else
                mapTiles[y][x].setFillColor(sf::Color::White);
        }

    //draws character
    float characterWidth = tileWidth - delta;
    float characterHeight = tileHeight - delta;
    sf::RectangleShape character ( sf::Vector2f(characterWidth, characterHeight) );
    float posX = static_cast<float>(subjectX) * tileWidth + delta;
    float posY = static_cast<float>(subjectY) * tileHeight + delta;
    character.setPosition( sf::Vector2f(posX, posY) );
    character.setFillColor(sf::Color::Red);
}