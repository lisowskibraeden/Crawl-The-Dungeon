//
// Created by Braeden on 8/28/2019.
//

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
                        if (allTiles[yPos][xPos - 1] == BASIC_TILE) { //enemies can only walk on the basic tiles
                            allTiles[yPos][xPos] = BASIC_TILE; //reset previous tile
                            xPos--; //change position
                            allTiles[yPos][xPos] = ENEMY_TILE; //change new tile
                        }
                    } else {
                        if (allTiles[yPos][xPos + 1] == BASIC_TILE) { //all work the same just for different cases
                            allTiles[yPos][xPos] = BASIC_TILE;
                            xPos++;
                            allTiles[yPos][xPos] = ENEMY_TILE;
                        }
                    }
                } else {
                    if (yPos/*enemy position*/ - positionY /*character postion*/ > 0) {
                        if (allTiles[yPos - 1][xPos] == BASIC_TILE) {
                            allTiles[yPos][xPos] = BASIC_TILE;
                            yPos--;
                            allTiles[yPos][xPos] = ENEMY_TILE;
                        }
                    } else {
                        if (allTiles[yPos + 1][xPos] == BASIC_TILE) {
                            allTiles[yPos][xPos] = BASIC_TILE;
                            yPos++;
                            allTiles[yPos][xPos] = ENEMY_TILE;
                        }
                    }
                }
            }
            attack(positionX, positionY, mainChar);
        }
    }
};