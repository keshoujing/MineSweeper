#include "logicController.h"

mt19937 logicController::random(time(0));
int logicController::flagCount;
bool logicController::isGameOver = false;
bool logicController::isDebugMode = false;
vector<int> logicController::checkedTail;
bool logicController::isGameWin = false;
vector<int> logicController::randomNumberCheck;
bool logicController::isTestMode = false;

void logicController::checkLeftClick(sf::Vector2<float> position) {
    //use FloatRect to check position.
    if (!isGameOver && !isGameWin){ // if game is not over.
        if (toolClass::getImageMap().at("debug").getImageRect().contains(position)){
            if (isDebugMode){
                isDebugMode = false;
            } else{
                isDebugMode = true;
            }
        } else {//it is not image
            for (int j = 0; j < toolClass::getTileVector().size(); ++j) {
                if (toolClass::getTileVector().at(j).getRect().contains(position)) {
                    if (!toolClass::getTileVector().at(j).getFlag()){
                        toolClass::getTileVector().at(j).Revealed();
                        toolClass::getTileVector().at(j).setClick(true);
                        checkedTail.clear();
                        for (int i = 0; i < toolClass::getTileVector().size(); ++i) { // check for all flag tile for revealNearTiles to skip them.
                            if (toolClass::getTileVector().at(i).getFlag()){
                                checkedTail.push_back(i);
                            }
                        }
                        revealNearTiles(j);
                    }
                }
            }
        }
    } // whether game is over or not.
        if (toolClass::getImageMap().at("face_happy").getImageRect().contains(position)){
            toolClass::reset();
        }else if (toolClass::getImageMap().at("test_1").getImageRect().contains(position)){
            ifstream file("boards/testboard1.brd", ios::in);
            testFunctionCombine(file);
            file.close();
        } else if (toolClass::getImageMap().at("test_2").getImageRect().contains(position)) {
            ifstream file("boards/testboard2.brd", ios::in);
            testFunctionCombine(file);
            file.close();
        } else if (toolClass::getImageMap().at("test_3").getImageRect().contains(position)) {
            ifstream file("boards/testboard3.brd", ios::in);
            testFunctionCombine(file);
            file.close();
        }

}

int logicController::getRandomNumber(int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    int rand = dist(random);
    for (int i = 0; i < randomNumberCheck.size(); ++i) {
        if (randomNumberCheck.at(i) == rand){
            rand = getRandomNumber(min, max);
            break;
        }
    }
    randomNumberCheck.push_back(rand);
    return rand;
}

int logicController::getFlagCount() {
    flagCount = 0;
    for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
        if (toolClass::getTileVector().at(i).getFlag()){
            flagCount++;
        }
    }
    return flagCount;
}

void logicController::checkFlagLocation(sf::Vector2<float> position) {
    if (!isGameWin && !isGameOver){
        for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
            if (toolClass::getTileVector().at(i).getRect().contains(position)){ // find which tile
                if (toolClass::getTileVector().at(i).getFlag()){ // if there already a flag
                    toolClass::getTileVector().at(i).setFlagTo(false); // set flag to false
                } else{ // there are not flag
                    toolClass::getTileVector().at(i).setFlagTo(true); // set flag to true
                }
            }
        }
    }
}

void logicController::checkIfRevealedAMIne() {
        for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
            // debug mode use same method, so isClick from tile.h is for here.
            if (toolClass::getTileVector().at(i).isReveal() && toolClass::getTileVector().at(i).isAMine() && toolClass::getTileVector().at(i).getClick()){
                isGameOver = true;
                for (int j = 0; j < toolClass::getTileVector().size(); ++j) {
                    if (toolClass::getTileVector().at(j).isAMine()){
                        toolClass::getTileVector().at(j).Revealed();
                    }
                }
            }
        }
}

bool logicController::getGameOver() {
    return isGameOver;
}

void logicController::setGameOver() {
    isGameOver = false;
}

bool logicController::getDebugMode() {
    return isDebugMode;
}

void logicController::checkNearByTiles() {
    //run toolClass::testEdge to check which tile is the edge of Y or X.
    int count;

    int XWidth = toolClass::getWidth() / 32;
    int Y[3] = {-XWidth, 0, XWidth};
    int X[3] = {-1, 0, 1};

    for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
        count = 0;
        //if in the middle, which have 8 near tile.
        if (!toolClass::getTileVector().at(i).getYEdge() && !toolClass::getTileVector().at(i).getXEdge()){
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (toolClass::getTileVector().at(i + Y[j] + X[k]).isAMine()){
                        count++;
                    }
                }
            }
        } else if (toolClass::getTileVector().at(i).getXEdge() && !toolClass::getTileVector().at(i).getYEdge()){
            //only in top X axis or button X axis.
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if ((i + Y[j] + X[k]) >= 0 && (i + Y[j] + X[k]) < toolClass::getTileVector().size()){
                        if (toolClass::getTileVector().at(i + Y[j] + X[k]).isAMine()){
                            count++;
                        }
                    }
                }
            }
        } else if (!toolClass::getTileVector().at(i).getXEdge() && toolClass::getTileVector().at(i).getYEdge()){
            //only in Y = 1 or Y = end axis.
            if (toolClass::getTileVector().at(i).getX() == 0){//means it is left side edge.
                for (int j = 0; j < 3; ++j) {
                    if (toolClass::getTileVector().at(i + Y[j]).isAMine()){count++;}
                    if (toolClass::getTileVector().at(i + Y[j] + 1).isAMine()){count++;}
                }
            } else{
                for (int j = 0; j < 3; ++j) {
                    if (toolClass::getTileVector().at(i + Y[j]).isAMine()){count++;}
                    if (toolClass::getTileVector().at(i + Y[j] - 1).isAMine()){count++;}
                }
            }
        } else if (toolClass::getTileVector().at(i).getXEdge() && toolClass::getTileVector().at(i).getYEdge()){
            // both is a X and Y edge, there are 4 tiles, each of them near 3 tiles.
            if (i == 0){ // first tail
                if (toolClass::getTileVector().at(i + 1).isAMine()){count++;}
                if (toolClass::getTileVector().at(i + XWidth).isAMine()){count++;}
                if (toolClass::getTileVector().at(i + XWidth + 1).isAMine()){count++;}
            } else if (i < toolClass::getTileVector().size() / 2){//second tail
                if (toolClass::getTileVector().at(i - 1).isAMine()){count++;}
                if (toolClass::getTileVector().at(i + XWidth).isAMine()){count++;}
                if (toolClass::getTileVector().at(i + XWidth - 1).isAMine()){count++;}
            } else if (i == toolClass::getTileVector().size() - 1){ //last tail
                if (toolClass::getTileVector().at(i - 1).isAMine()){count++;}
                if (toolClass::getTileVector().at(i - XWidth).isAMine()){count++;}
                if (toolClass::getTileVector().at(i - XWidth - 1).isAMine()){count++;}
            }else if (i >= toolClass::getTileVector().size() / 2){//third tail
                if (toolClass::getTileVector().at(i + 1).isAMine()){count++;}
                if (toolClass::getTileVector().at(i - XWidth).isAMine()){count++;}
                if (toolClass::getTileVector().at(i - XWidth + 1).isAMine()){count++;}
            }
        } else{
            cout << "error" << endl;
        }
        toolClass::getTileVector().at(i).setNumber(count);
    }
}

void logicController::clearNearTiles() {
    for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
        toolClass::getTileVector().at(i).setNumber(0);
    }
}

int logicController::revealNearTiles(int whichTile) {
    int widthSize = toolClass::getWidth() / 32;
    for (int i = 0; i < checkedTail.size(); ++i) {
        if (checkedTail.at(i) == whichTile){
            return -1;
        }
    }
    checkedTail.push_back(whichTile);
    if (whichTile >= 0 && whichTile < toolClass::getTileVector().size()){
        if (!toolClass::getTileVector().at(whichTile).isAMine() && toolClass::getTileVector().at(whichTile).getNumber() == 0){
                toolClass::getTileVector().at(whichTile).Revealed();
                toolClass::getTileVector().at(whichTile).setClick(true);
                revealNearTiles_SpecialCase(whichTile);
            if (toolClass::getTileVector().at(whichTile).getYEdge()) {
                if (toolClass::getTileVector().at(whichTile).getX() / 32 == 0) {
                    revealNearTiles(whichTile + 1);
                } else {
                    revealNearTiles(whichTile - 1);
                }
            } else{
                revealNearTiles(whichTile - 1);
                revealNearTiles(whichTile + 1);
            }
            revealNearTiles(whichTile + widthSize);
            revealNearTiles(whichTile - widthSize);
        } else{
            if (!toolClass::getTileVector().at(whichTile).getFlag()){
                toolClass::getTileVector().at(whichTile).Revealed();
                toolClass::getTileVector().at(whichTile).setClick(true);
            }
            return -1;
        }
    }
}

void logicController::checkWinCondition() {
    int count = 0;
    int count2 = 0;
    int revealedTill = 0;
    for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
        if (!toolClass::getTileVector().at(i).getClick()){
            count++;
        }
        if (toolClass::getTileVector().at(i).isAMine() && toolClass::getTileVector().at(i).getFlag()){
            count2++;
        }
    }
    if (count == toolClass::getMineCount() || (count2 == toolClass::getMineCount() && count2 == logicController::getFlagCount())){
        isGameWin = true;
        isDebugMode = false;
        for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
            if (toolClass::getTileVector().at(i).isAMine()){
                toolClass::getTileVector().at(i).setFlagTo(true);
            }
        }
    }
}

void logicController::setGameWin() {
    isGameWin = false;
}

bool logicController::getGameWin() {
    return isGameWin;
}

void logicController::SetTestModeTo(bool what) {
    isTestMode = what;
}

//bool logicController::getTestMode() {
//    return isTestMode;
//}

void logicController::clearRandomCheckVector() {
    randomNumberCheck.clear();
}

void logicController::revealNearTiles_SpecialCase(int whichTail) {
    int XWidth = toolClass::getWidth() / 32;
    int fourTail[4] = {-XWidth - 1, -XWidth + 1, XWidth - 1 ,XWidth + 1};

    if (!toolClass::getTileVector().at(whichTail).getXEdge() && !toolClass::getTileVector().at(whichTail).getYEdge()){
        if (!toolClass::getTileVector().at(whichTail).isAMine() && toolClass::getTileVector().at(whichTail).getNumber() == 0 && !toolClass::getTileVector().at(whichTail).getFlag()){
            if (toolClass::getTileVector().at(whichTail).isReveal()){
                for (int i = 0; i < 4; ++i) {
                    if (whichTail + fourTail[i] >= 0 && whichTail + fourTail[i] < toolClass::getTileVector().size()){
                        if (!toolClass::getTileVector().at(whichTail + fourTail[i]).isAMine() && !toolClass::getTileVector().at(whichTail + fourTail[i]).getFlag()){
                            toolClass::getTileVector().at(whichTail + fourTail[i]).Revealed();
                            toolClass::getTileVector().at(whichTail + fourTail[i]).setClick(true);
                        }
                    }
                }
            }
        }
    }
}

void logicController::testFunctionCombine(ifstream & file) {
    for (int i = 0; i < toolClass::getTileVector().size(); ++i) {
        toolClass::getTileVector().at(i).reset();
    }
    isGameWin = false;
    isGameOver = false;
    isDebugMode = false;
    toolClass::loadTest123(file);
    toolClass::loadMineForTest123();
    logicController::clearNearTiles();
    logicController::checkNearByTiles();
    isTestMode = true;
}



