//
// Created by gionimbus on 7/23/25.
//

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MapView.h"

constexpr int windowWidth= 1000;
constexpr int windowHeight = 1000;

MapView::MapView(GameCharacter* gc) {

    const GlobalMap& map = GlobalMap::getInstance();
    mapWidth = map.getWidth();
    mapHeight = map.getHeight();

    subject = gc;
    subjectX =  gc->getX();
    subjectY = gc->getY();

    window.create( sf::VideoMode(windowWidth, windowHeight), "A* Game", sf::Style::Close | sf::Style::Titlebar );

    //setup map tiles
    mapTiles = std::vector<std::vector<sf::RectangleShape>> (map.getHeight(), std::vector<sf::RectangleShape> (map.getWidth()));
    tileWidth = ( static_cast<float>(windowWidth) / map.getWidth() );
    tileHeight = ( static_cast<float>(windowHeight) / map.getHeight() );

    for (int y = 0; y < map.getHeight(); y++)
        for (int x = 0; x < map.getWidth(); x++) {
            mapTiles[y][x].setSize( sf::Vector2f( tileWidth, tileHeight ) );
            mapTiles[y][x].setPosition( (x * tileWidth), (y * tileHeight) );
            if (map.getValue(x, y) == 9) {
                mapTiles[y][x].setFillColor(sf::Color::Black);
                //mapTiles[y][x].setOutlineThickness(1);
                //mapTiles[y][x].setOutlineColor(sf::Color::White);
            } else
                mapTiles[y][x].setFillColor(sf::Color::White);
        }

    //setup character
    characterWidth = tileWidth;
    characterHeight = tileHeight;
    character = sf::RectangleShape ( sf::Vector2f(characterWidth, characterHeight) );
    character.setFillColor(sf::Color::Red);
}

void MapView::update() {
    subjectX = subject->getX();
    subjectY = subject->getY();
}

void MapView::attach() {
    subject->subscribe(this);
}

void MapView::detach() {
    subject->unsubscribe(this);
}

void MapView::drawMap() {
    for (int y = 0; y < mapHeight; y++)
        for (int x = 0; x < mapWidth; x++)
            window.draw(mapTiles[y][x]);
}

void MapView::drawCharacter() {
    float posX = subjectX * tileWidth;
    float posY = subjectY * tileHeight;
    character.setPosition(posX, posY);

    //draw character
    window.draw(character);
}

void MapView::render() {
    window.clear();
    drawMap();
    drawCharacter();
    window.display();
}

