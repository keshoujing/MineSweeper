#include "toolClass.h"

unordered_map<string, sf::Texture> toolClass::textures;
float toolClass::width, toolClass::height;
int toolClass::MineCount, toolClass::tileCount;
vector<tile> toolClass::tileVector;
unordered_map<string, controlImage> toolClass::controlImageMap;
unordered_map<int, sf::Sprite> toolClass::MineCounterDigitSet;
unordered_map<int, sf::Sprite> toolClass::numbers;
int toolClass::MineCountOriginal;

sf::Texture& toolClass::getTexture(string fileName) {
    if (textures.find(fileName) == textures.end()) // if file name is not match texture in side of map.
    {
        string path = "images/" + fileName + ".png"; // create to map.
        textures[fileName].loadFromFile(path);
    }

    return textures[fileName];
}

void toolClass::loadConfigFile() {
    ifstream file("boards/config.cfg", ios::in);
    string read;
    getline(file, read);
    width = stof(read) * 32;
    getline(file, read);
    height = stof(read) * 32 + 88;
    getline(file, read);
    MineCount = stoi(read);
    file.close();
    tileCount = (width / 32) * ((height - 88) / 32);
    MineCountOriginal = MineCount;
}

void toolClass::loadTile() {
    sf::Sprite sprite;
    sprite.setTexture(getTexture("tile_hidden"));
    float widthTileCount = 0;
    float heightTileCount = 0;
    int widthCount = width / 32;
    for (int i = 0; i < tileCount; ++i) {
        if (widthTileCount < widthCount){
//            cout <<widthTileCount <<endl;
//            cout << widthCount << endl;
            tileVector.push_back(tile(widthTileCount * 32, heightTileCount * 32));
            sprite.setPosition(widthTileCount * 32, heightTileCount * 32);
            tileVector.at(i).setRect(sprite);
            if (heightTileCount == 0 || heightTileCount == (height -88) / 32 - 1){
                tileVector.at(i).setXEdge(true);
            }
            widthTileCount++;
        } else{
            widthTileCount = 0;
            heightTileCount++;
            tileVector.push_back(tile(widthTileCount * 32, heightTileCount * 32));
            sprite.setPosition(widthTileCount * 32, heightTileCount * 32);
            tileVector.at(i).setRect(sprite);
            tileVector.at(i - 1).setYEdge(true);
            tileVector.at(i).setYEdge(true);
            widthTileCount++;
            if (heightTileCount == 0 || heightTileCount == (height -88) / 32 - 1){
                tileVector.at(i).setXEdge(true);
            }
        }
    }
    tileVector.at(0).setYEdge(true);
    tileVector.at(tileVector.size() - 1).setYEdge(true);
}

void toolClass::disPlayTile(sf::RenderWindow &window) {
    sf::Sprite sprite;
    sprite.setTexture(getTexture("tile_hidden"));
    sf::Sprite sprite2;
    sprite2.setTexture(getTexture("tile_revealed"));

    for (int i = 0; i < tileVector.size(); ++i) {
        if (tileVector.at(i).isReveal()){
            sprite2.setPosition(tileVector.at(i).getX(), tileVector.at(i).getY());
            window.draw(sprite2);
        } else{
            sprite.setPosition(tileVector.at(i).getX(), tileVector.at(i).getY());
            window.draw(sprite);
        }
    }
}

float toolClass::getWidth() {return width;}

float toolClass::getHeight() {return height;}

void toolClass::displayControlImage(sf::RenderWindow &window) {
    //debug
    window.draw(controlImageMap.at("debug").getSprite());
    //test123
    window.draw(controlImageMap.at("test_1").getSprite());
    window.draw(controlImageMap.at("test_2").getSprite());
    window.draw(controlImageMap.at("test_3").getSprite());
    //face need change
    if (logicController::getGameOver()){
        window.draw(controlImageMap.at("face_lose").getSprite());
    } else if(logicController::getGameWin()) {
        window.draw(controlImageMap.at("face_win").getSprite());
    } else {
        window.draw(controlImageMap.at("face_happy").getSprite());
    }

}

void toolClass::loadControlImage() {
    int Y = tileVector.at(tileVector.size() - 1).getY() + 32;
    sf::Sprite sprite;
    //happy face
    sprite.setTexture(getTexture("face_happy"));
    sprite.setPosition(width / 2 - 32 - 16, Y);
    controlImage fh(sprite);
    //face win
    sprite.setTexture(getTexture("face_win"));
    sprite.setPosition(width / 2 - 32 - 16, Y);
    controlImage fw(sprite);
    //face lose
    sprite.setTexture(getTexture("face_lose"));
    sprite.setPosition(width / 2 - 32 - 16, Y);
    controlImage fl(sprite);
    //debug
    sprite.setTexture(getTexture("debug"));
    sprite.setPosition(width / 2 + 80, Y);
    controlImage dw(sprite);
    //test_1
    sprite.setTexture(getTexture("test_1"));
    sprite.setPosition(width / 2 + 144, Y);
    controlImage t1(sprite);
    //test_2
    sprite.setTexture(getTexture("test_2"));
    sprite.setPosition(width / 2 + 208, Y);
    controlImage t2(sprite);
    //test_3
    sprite.setTexture(getTexture("test_3"));
    sprite.setPosition(width / 2 + 272, Y);
    controlImage t3(sprite);

    controlImageMap.insert(make_pair("face_happy", fh));
    controlImageMap.insert(make_pair("face_win", fw));
    controlImageMap.insert(make_pair("face_lose", fl));
    controlImageMap.insert(make_pair("debug", dw));
    controlImageMap.insert(make_pair("test_1", t1));
    controlImageMap.insert(make_pair("test_2", t2));
    controlImageMap.insert(make_pair("test_3", t3));
}

void toolClass::clearTexture() {
    textures.clear();
}

vector<tile>& toolClass::getTileVector() {
    return tileVector;
}

unordered_map<string, controlImage> &toolClass::getImageMap() {
    return controlImageMap;
}

void toolClass::displayMine(sf::RenderWindow &window) {
    sf::Sprite sprite;
    sprite.setTexture(getTexture("mine"));
    for (int i = 0; i < tileCount; ++i) {
        if (tileVector.at(i).isAMine() && tileVector.at(i).isReveal()){
            sprite.setPosition(tileVector.at(i).getX(), tileVector.at(i).getY());
            window.draw(sprite);
        }
    }

    if (logicController::getGameOver()){
        for (int i = 0; i < tileCount; ++i) {
            if (tileVector.at(i).isAMine()){
                tileVector.at(i).Revealed();
            }
        }
    }

    //debug
    if(logicController::getDebugMode()){
        for (int i = 0; i < tileCount; ++i) {
            if (tileVector.at(i).isAMine()){
                sprite.setPosition(tileVector.at(i).getX(), tileVector.at(i).getY());
                window.draw(sprite);
            }
            if (tileVector.at(i).isAMine() && !tileVector.at(i).getClick()){ // if no click check, mine will always be unrevealed.
                tileVector.at(i).setRevealToFalse();
            }
        }
    }
}

void toolClass::loadMine() {
    for (int i = 0; i < MineCount; ++i) {
        tileVector.at(logicController::getRandomNumber(0, tileCount - 1)).AMine();
    }
}

void toolClass::loadMineCounter() {
    sf::Sprite sprite;
    sprite.setTexture(getTexture("digits"));

    int count = 0;
    for (int i = 0; i < 12; ++i) {
        //each of rectLeft is 21.
       sprite.setTextureRect(sf::IntRect(count, 0, 21, 32));
       MineCounterDigitSet.insert(make_pair(i,sprite));
       count += 21;
    }

}

void toolClass::displayMineCounter(sf::RenderWindow &window) {
    float Y = tileVector.at(tileVector.size() - 1).getY() + 32;
    float X[3] = {16, 37, 58};
    int count = MineCount - logicController::getFlagCount();
    string temp = to_string(count);

    while (temp.size() != 3 || temp.at(0) == '-'){
        if (count >= 0){
            temp = "0" + temp;
        } else {
            temp = temp.substr(1);
            if (temp.size() != 3){
                temp = "0" + temp;
                if (temp.size() != 3){ // what if it is -1. 01??
                    temp = "0" + temp;
                }
                break;
            }
        }
    }
    if (count < 0) {
        MineCounterDigitSet.at(11).setTextureRect(sf::IntRect(210, 0, 21, 32));
        MineCounterDigitSet.at(11).setPosition(0, Y);
        window.draw(MineCounterDigitSet.at(11));
    }
        for (int i = 0; i < 3; ++i) {
            //char to int, ascii, 0 start from 48.
            MineCounterDigitSet.at((int) temp.at(i) - 48).setPosition(X[i], Y);
            window.draw(MineCounterDigitSet.at((int) temp.at(i) - 48));
        }

}

void toolClass::displayFlag(sf::RenderWindow &window) {
    sf::Sprite sprite;
    sprite.setTexture(getTexture("flag"));
    for (int i = 0; i < tileVector.size(); ++i) {
        if (tileVector.at(i).getFlag()){
            sprite.setPosition(tileVector.at(i).getX(), tileVector.at(i).getY());
            window.draw(sprite);
        }
    }
}

void toolClass::reset() {
    for (int i = 0; i < tileVector.size(); ++i) {
        tileVector.at(i).reset();
    }

    logicController::clearRandomCheckVector();
    logicController::setGameOver();
    MineCount = MineCountOriginal;
    loadMine();
    loadMineForTest123();
    logicController::clearNearTiles();
    logicController::checkNearByTiles();
    logicController::setGameWin();
    logicController::SetTestModeTo(false);
}

void toolClass::loadNumbers() {
    sf::Sprite sprite;
    string num;
    for (unsigned int i = 1; i < 9; ++i) {
        num = "number_" + to_string(i);
        sprite.setTexture(getTexture(num));
        numbers.insert(make_pair(i, sprite));
    }
}

unordered_map<int, sf::Sprite> &toolClass::getNumbers() {
    return numbers;
}

void toolClass::displayNumbers(sf::RenderWindow &window) {
    for (int i = 0; i < tileVector.size(); ++i) {
        if (tileVector.at(i).getClick() && !tileVector.at(i).isAMine() && tileVector.at(i).getNumber() != 0 && tileVector.at(i).isReveal()){
            numbers.at(tileVector.at(i).getNumber()).setPosition(tileVector.at(i).getX(), tileVector.at(i).getY());
            window.draw(numbers.at(tileVector.at(i).getNumber()));
        }
    }
}


//void toolClass::testEdge() {
//    int widthCount = width / 32;
//    int a= 0;
//    int b=0;
//    for (int i = 0; i < tileCount; ++i) {
//        if (a < widthCount){
//            if (tileVector.at(i).getXEdge() && tileVector.at(i).getYEdge()){
//                cout << "+";
//            } else if (tileVector.at(i).getXEdge()){
//                cout << 1;
//            }else if (tileVector.at(i).getYEdge()){
//                cout << 2;
//            }else{
//                cout << 0;
//            }
//            a++;
//        } else{
//            a = 0;
//            cout << endl;
//            b++;
//            if (tileVector.at(i).getXEdge() && tileVector.at(i).getYEdge()){
//                cout << "+";
//            } else if (tileVector.at(i).getXEdge()){
//                cout << 1;
//            }else if (tileVector.at(i).getYEdge()){
//                cout << 2;
//            }else{
//                cout << 0;
//            }
//            a++;
//        }
//    }
//    cout << endl;
//    cout << endl;
//}
//
//void toolClass::testTile() {
//    tileVector.at(119).Revealed();
//    tileVector.at(119 - 25).Revealed();
//}

int toolClass::getMineCount() {
    return MineCount;
}

void toolClass::loadTest123(ifstream &file) {
    string temp;
    int Y = 0;
    while (!file.eof()){
        getline(file, temp);
        for (int i = 0; i < 25; ++i) {
            if (temp.at(i) == '1'){
                tileVector.at(25 * Y + i).AMine();
            }
        }
        Y++;
    }
}

//void toolClass::clearMine() {
//    for (int i = 0; i < tileVector.size(); ++i) {
//        tileVector.at(i).setIsAMineToFalse();
//    }
//}

//void toolClass::clearRevealedTile() {
//    for (int i = 0; i < tileVector.size(); ++i) {
//        if (tileVector.at(i).isReveal()){
//            tileVector.at(i).setRevealToFalse();
//        }
//    }
//}

void toolClass::loadMineForTest123() {
    int MineCountForTest = 0;
    for (int i = 0; i < tileVector.size(); ++i) {
        if (tileVector.at(i).isAMine()){
            MineCountForTest++;
        }
    }
    MineCount = MineCountForTest;
}









