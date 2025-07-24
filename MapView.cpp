//
// Created by gionimbus on 7/23/25.
//

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MapView.h"

constexpr int windowWidth= 800;
constexpr int windowHeight = 800;
constexpr float delta = 5.0;

MapView::MapView(GameCharacter *gameCharacter): subject(gameCharacter) {
    const GlobalMap& map = GlobalMap::getInstance();
    tileWidth = ( static_cast<float>(windowWidth) / map.getWidth() );
    tileHeight = ( static_cast<float>(windowHeight) / map.getHeight() );
    tileSize = sf::Vector2f (tileWidth, tileHeight);

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

void MapView::drawMap() {
    const GlobalMap& map = GlobalMap::getInstance();

    //setup map tiles
    std::vector<std::vector<sf::RectangleShape>> mapTiles (map.getHeight(), std::vector<sf::RectangleShape> (map.getWidth()));

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

    //draw map tiles
    for (int y = 0; y < map.getHeight(); y++)
        for (int x = 0; x < map.getWidth(); x++)
            window.draw(mapTiles[y][x]);
}

void MapView::drawCharacter() {
    //setup character
    float characterWidth = tileWidth - delta;
    float characterHeight = tileHeight - delta;
    sf::RectangleShape character ( sf::Vector2f(characterWidth, characterHeight) );
    float posX = subjectX * tileWidth + delta;
    float posY = subjectY * tileHeight + delta;
    character.setPosition(posX, posY);
    character.setFillColor(sf::Color::Red);

    //draw character
    window.draw(character);
}

bool MapView::drawPath(const std::vector<SearchState>& path) {
    if (path.empty())
        return false;

    const GlobalMap& map = GlobalMap::getInstance();

    //setup path tiles
    std::vector<sf::RectangleShape> tiles (path.size());

    for (int i = 1; i < tiles.size(); i++) {
        tiles[i].setSize(tileSize);
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