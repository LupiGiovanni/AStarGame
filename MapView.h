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
    explicit MapView (GameCharacter* gameCharacter);

    void update() override;
    void attach() override;
    void detach() override;

    void drawMap();
    bool drawPath (const std::vector<SearchState>& path);

private:
    int subjectX;
    int subjectY;
    GameCharacter* subject;

    sf::RenderWindow window;
    static inline sf::Vector2f tileSize = sf::Vector2f (0.0, 0.0);
    static inline float tileWidth = 0;
    static inline float tileHeight = 0;
};


#endif //MAPVIEW_H
