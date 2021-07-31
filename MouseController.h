#ifndef MAIN_CPP_MouseManager_H
#define MAIN_CPP_MouseManager_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "logicController.h"

using namespace std;

class MouseController {

    static sf::Vector2<float> position;

public:
    static void leftClicked(sf::RenderWindow &window, sf::Mouse mouse);

    static void rightClicked(sf::RenderWindow &window, sf::Mouse mouse);

    //static void setPosition(sf::RenderWindow &window, sf::Mouse mouse);

    //static sf::Vector2<float> getPosition();
};

#endif
