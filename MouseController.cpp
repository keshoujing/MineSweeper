#include "MouseController.h"

sf::Vector2<float> MouseController::position;


void MouseController::leftClicked(sf::RenderWindow &window, sf::Mouse mouse) {
    sf::Vector2<float> position;
    position.x = mouse.getPosition(window).x;
    position.y = mouse.getPosition(window).y;
    logicController::checkLeftClick(position);
}

void MouseController::rightClicked(sf::RenderWindow &window, sf::Mouse mouse) {
    if (!logicController::getGameOver()){
        sf::Vector2<float> position;
        position.x = mouse.getPosition(window).x;
        position.y = mouse.getPosition(window).y;
        logicController::checkFlagLocation(position);
    }
}

//sf::Vector2<float> MouseController::getPosition() {
//    return position;
//}
//
//void MouseController::setPosition(sf::RenderWindow &window, sf::Mouse mouse) {
//    position.x = mouse.getPosition(window).x;
//    position.y = mouse.getPosition(window).y;
//}

