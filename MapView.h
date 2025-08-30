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

    void render();

    sf::RenderWindow& getWindow() { return window; }
    float getTileWidth() const { return tileWidth; }
    float getTileHeight() const { return tileHeight; }

private:
    int mapWidth;
    int mapHeight;
    void drawMap();

    GameCharacter* subject;
    int subjectX;
    int subjectY;

    sf::RenderWindow window;

    std::vector<std::vector<sf::RectangleShape>> mapTiles;
    float tileWidth;
    float tileHeight;
    sf::Texture grassTexture;
    sf::Texture stoneTexture;
    bool loadTextures();
    bool setUpMapTiles();

    sf::RectangleShape character;
    float characterWidth;
    float characterHeight;
    float margin;
    void setUpCharacter();
    void drawCharacter();
};


#endif //MAPVIEW_H
