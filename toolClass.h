#ifndef PROJECT3_TOOLCLASS_H
#define PROJECT3_TOOLCLASS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "tile.h"
#include "controlImage.h"
#include "logicController.h"
#include "MouseController.h"

using namespace std;

class toolClass {

    static unordered_map<string, sf::Texture> textures;
    static float width, height;
    static int MineCount, tileCount;
    static vector<tile> tileVector;
    static unordered_map<string, controlImage> controlImageMap;
    static unordered_map<int, sf::Sprite> MineCounterDigitSet;
    static unordered_map<int, sf::Sprite> numbers;
    static int MineCountOriginal;

public:
    static float getWidth();

    static float getHeight();

    static int getMineCount();

public:
    static sf::Texture &getTexture(string fileName);

    static void loadConfigFile();

    static void loadTile();

    static void disPlayTile(sf::RenderWindow &window);

    static void displayControlImage(sf::RenderWindow &window);

    static void loadControlImage();

    static void clearTexture();

    static vector<tile>& getTileVector();

    static unordered_map<string, controlImage>& getImageMap();

    static void displayMine(sf::RenderWindow &window);

    static void loadMine();

    static void loadMineCounter();

    static void displayMineCounter(sf::RenderWindow &window);

    static void displayFlag(sf::RenderWindow &window);

    static void reset();

    static void loadNumbers();

    static unordered_map<int, sf::Sprite>& getNumbers();

    static void displayNumbers(sf::RenderWindow &window);

    //static void testEdge(); // test passed.

    //static void testTile();

    static void loadTest123(ifstream &file);

    //static void clearMine();

    //static void clearRevealedTile();

    static void loadMineForTest123();
};


#endif //PROJECT3_TOOLCLASS_H
