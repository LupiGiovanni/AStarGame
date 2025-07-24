//
// Created by gionimbus on 7/23/25.
//

#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameCharacter.h"


class MapView : public Observer {
public:
    explicit MapView (GameCharacter* gameCharacter);

    void update() override;
    void attach() override;
    void detach() override;

    void draw();

private:
    int subjectX;
    int subjectY;
    GameCharacter* subject;

    sf::RenderWindow window;
};


#endif //MAPVIEW_H
