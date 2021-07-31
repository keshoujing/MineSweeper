#ifndef PROJECT3_LOGICCONTROLLER_H
#define PROJECT3_LOGICCONTROLLER_H

#include <SFML/Graphics.hpp>
#include "toolClass.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

class logicController {

    static mt19937 random;
    static int flagCount;
    static bool isGameOver;
    static bool isDebugMode;
    static vector<int> checkedTail;
    static bool isGameWin;
    static vector<int> randomNumberCheck;
    static bool isTestMode;

public:
    static bool getGameOver();

    static void setGameOver();

    static bool getDebugMode();

    static bool getGameWin();

    static void setGameWin();

    static void SetTestModeTo(bool what);

    //static bool getTestMode();


public:
    static void checkLeftClick(sf::Vector2<float> position);

    static int getRandomNumber(int min, int max);

    static int getFlagCount();

    static void checkFlagLocation(sf::Vector2<float> position);

    static void checkIfRevealedAMIne();

    static void checkNearByTiles(); //find out all the numbers in the tile.

    static void clearNearTiles();   //for reset use only, clear all number store in class.

    static int revealNearTiles(int whichTile);  //if the tile has 0 near by mines, just reveal it.

    static void checkWinCondition();

    static void clearRandomCheckVector();

    static void revealNearTiles_SpecialCase(int whichTail);

    static void testFunctionCombine(ifstream &file);

};


#endif //PROJECT3_LOGICCONTROLLER_H
