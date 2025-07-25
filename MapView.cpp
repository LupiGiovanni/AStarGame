//
// Created by gionimbus on 7/23/25.
//

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MapView.h"

constexpr int windowWidth= 800;
constexpr int windowHeight = 800;
constexpr float delta = 5.0;

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
                mapTiles[y][x].setOutlineThickness(1);
                mapTiles[y][x].setOutlineColor(sf::Color::White);
            } else
                mapTiles[y][x].setFillColor(sf::Color::White);
        }

    //setup character
    characterWidth = tileWidth - delta;
    characterHeight = tileHeight - delta;
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
    float posX = subjectX * tileWidth + delta;
    float posY = subjectY * tileHeight + delta;
    character.setPosition(posX, posY);

    //draw character
    window.draw(character);
}

bool MapView::drawPath(const std::vector<SearchState>& path) {
    if (path.empty())
        return false;

    //setup path tiles
    std::vector<sf::RectangleShape> tiles (path.size());

    for (int i = 1; i < tiles.size(); i++) {
        tiles[i].setSize( sf::Vector2f( tileWidth, tileHeight ) );
        float posX = path[i].getX() * tileWidth;
        float posY = path[i].getY() * tileHeight;
        tiles[i].setPosition(posX, posY);
        tiles[i].setFillColor(sf::Color(140, 140, 255));
        tiles[i].setOutlineThickness(1.0);
        tiles[i].setOutlineColor(sf::Color::White);
    }

    //draw path tiles
    for (const auto& element : tiles)
        window.draw(element);

    return true;
}

void MapView::display() {
    window.display();
}

v
