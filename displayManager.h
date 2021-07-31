#ifndef PROJECT3_DISPLAYMANAGER_H
#define PROJECT3_DISPLAYMANAGER_H

#include <iostream>
#include "toolClass.h"

using namespace std;

class displayManager {

public:
    static void gameStart(sf::RenderWindow &window);

    static void gameBefore();

    static void gameProcessing();
};


#endif //PROJECT3_DISPLAYMANAGER_H
