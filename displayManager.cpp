#include "displayManager.h"

void displayManager::gameStart(sf::RenderWindow &window) {
    toolClass::displayControlImage(window);
    toolClass::disPlayTile(window);
    toolClass::displayMineCounter(window);
    toolClass::displayFlag(window);
    toolClass::displayMine(window);
    toolClass::displayNumbers(window);
}

void displayManager::gameBefore() {
    toolClass::loadConfigFile();
    toolClass::loadTile();
    toolClass::loadControlImage();
    toolClass::loadMine();
    toolClass::loadMineCounter();
    toolClass::loadNumbers();
    logicController::checkNearByTiles();
}


void displayManager::gameProcessing() {
    logicController::checkIfRevealedAMIne();
    logicController::checkWinCondition();
    //toolClass::testEdge(); // test passed.
}
