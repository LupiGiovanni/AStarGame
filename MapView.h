//
// Created by gionimbus on 7/23/25.
//

#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SearchState.h"
#include "GameCharacter.h"


class MapView : public Observer {
public:
    explicit MapView (GameCharacter* gc);

    void update() override;
    void attach() override;
    void detach() override;

    void drawMap();
    void drawCharacter();
    bool drawPath (const std::vector<SearchState>& path);
    void display();
    void clear();

private:
    int mapWidth;
    int mapHeight;

    GameCharacter* subject;
    int subjectX;
    int subjectY;

    sf::RenderWindow window;

    std::vector<std::vector<sf::RectangleShape>> mapTiles;
    float tileWidth;
    float tileHeight;

    sf::RectangleShape character;
    float characterWidth;
    float characterHeight;

};


#endif //MAPVIEW_H
