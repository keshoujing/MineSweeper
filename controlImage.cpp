//
// Created by 38658 on 2021/7/19.
//

#include "controlImage.h"

controlImage::controlImage(sf::Sprite sprite) {
    this->sprite = sprite;
    rect = sprite.getGlobalBounds();
}

sf::FloatRect controlImage::getImageRect() {
    return rect;
}

sf::Sprite controlImage::getSprite() {
    return sprite;
}
