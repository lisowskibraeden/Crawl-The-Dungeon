#include <cmath>
#include "TilesEnum.cpp"
#include "Character.cpp"

class Soldier {
public:
    bool attacked = false;
    int movement;
    int xPos;
    int yPos;

    Soldier(int x, int y) {
        xPos = x;
        yPos = y;
        movement = 1;
    }

    void attack(int positionX, int positionY, Character *mainChar) { //enemy attack
        if (!attacked) {
            if (((abs((xPos - positionX)) <= movement) && (abs((yPos - positionY)) <= 0)) ||
                ((abs((yPos - positionY)) == (movement)) &&
                 (abs((xPos - positionX)) <= 0))) { //checks to see if the player is near the enemy
                mainChar->healthDown();
            }
        }
    }

    void move(int positionX, int positionY, int allTiles[34][60], Character *mainChar) {
        if (!attacked) { //make sure the enemy hasn't attacked
            for (int i = movement; i > 0; i--) {
                if (abs(xPos - positionX) >= abs(yPos -
                                                 positionY)) {//basic AI essentially if the player is more horizontally further go horizontal otherwise go vertical
                    if (xPos - positionX > 0) {
                        if (!moveR(positionX, positionY, allTiles)) {
                            findNextMove(positionX, positionY, allTiles, 'R');
                        }
                    } else {
                        if (!moveL(positionX, positionY, allTiles)) {
                            findNextMove(positionX, positionY, allTiles, 'L');
                        }
                    }
                } else {
                    if (yPos/*enemy position*/ - positionY /*character postion*/ > 0) {
                        if (!moveU(positionX, positionY, allTiles)) {
                            findNextMove(positionX, positionY, allTiles, 'U');
                        }
                    } else {
                        if (!moveD(positionX, positionY, allTiles)) {
                            findNextMove(positionX, positionY, allTiles, 'D');
                        }
                    }
                }
            }
            attack(positionX, positionY, mainChar);
        }
    }

    bool moveR(int positionX, int positionY, int allTiles[34][60]) {
        if (allTiles[yPos][xPos - 1] == BASIC_TILE) { //enemies can only walk on the basic tiles
            allTiles[yPos][xPos] = BASIC_TILE; //reset previous tile
            xPos--; //change position
            allTiles[yPos][xPos] = ENEMY_TILE; //change new tile
            return true;
        } else {
            return false;
        }
    }

    bool moveL(int positionX, int positionY, int allTiles[34][60]) {
        if (allTiles[yPos][xPos + 1] == BASIC_TILE) { //all work the same just for different cases
            allTiles[yPos][xPos] = BASIC_TILE;
            xPos++;
            allTiles[yPos][xPos] = ENEMY_TILE;
            return true;
        } else {
            return false;
        }
    }

    bool moveU(int positionX, int positionY, int allTiles[34][60]) {
        if (allTiles[yPos - 1][xPos] == BASIC_TILE) {
            allTiles[yPos][xPos] = BASIC_TILE;
            yPos--;
            allTiles[yPos][xPos] = ENEMY_TILE;
            return true;
        } else {
            return false;
        }
    }

    bool moveD(int positionX, int positionY, int allTiles[34][60]) {
        if (allTiles[yPos + 1][xPos] == BASIC_TILE) {
            allTiles[yPos][xPos] = BASIC_TILE;
            yPos++;
            allTiles[yPos][xPos] = ENEMY_TILE;
            return true;
        } else {
            return false;
        }
    }

    void findNextMove(int positionX, int positionY, int allTiles[34][60], char lastCheck) {
        switch (lastCheck) {
            case 'U':
                if (xPos - positionX > 0) {
                    if (!moveR(positionX, positionY, allTiles)) {
                        if (!moveL(positionX, positionY, allTiles)) {
                            if (!moveD(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                } else {
                    if (!moveL(positionX, positionY, allTiles)) {
                        if (!moveR(positionX, positionY, allTiles)) {
                            if (!moveD(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                }
                break;
            case 'D':
                if (xPos - positionX > 0) {
                    if (!moveR(positionX, positionY, allTiles)) {
                        if (!moveL(positionX, positionY, allTiles)) {
                            if (!moveU(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                } else {
                    if (!moveL(positionX, positionY, allTiles)) {
                        if (!moveR(positionX, positionY, allTiles)) {
                            if (!moveU(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                }
                break;
            case 'R':
                if (yPos/*enemy position*/ - positionY /*character postion*/ > 0) {
                    if (!moveU(positionX, positionY, allTiles)) {
                        if (!moveD(positionX, positionY, allTiles)) {
                            if (!moveL(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                } else {
                    if (!moveD(positionX, positionY, allTiles)) {
                        if (!moveU(positionX, positionY, allTiles)) {
                            if (!moveL(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                }
                break;
            case 'L':
                if (yPos/*enemy position*/ - positionY /*character postion*/ > 0) {
                    if (!moveU(positionX, positionY, allTiles)) {
                        if (!moveD(positionX, positionY, allTiles)) {
                            if (!moveR(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                } else {
                    if (!moveD(positionX, positionY, allTiles)) {
                        if (!moveU(positionX, positionY, allTiles)) {
                            if (!moveR(positionX, positionY, allTiles)) {
                                //enemy is surrounded
                            }
                        }
                    }
                }
                break;
        }
    }

};
