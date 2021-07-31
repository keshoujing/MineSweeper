#ifndef PROJECT3_CONTROLIMAGE_H
#define PROJECT3_CONTROLIMAGE_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class controlImage {

    sf::Sprite sprite;
    sf::FloatRect rect;

public:
    controlImage(sf::Sprite sprite);

    sf::FloatRect getImageRect();

    sf::Sprite getSprite();

};


#endif //PROJECT3_CONTROLIMAGE_H
