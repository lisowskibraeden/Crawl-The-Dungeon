//
// Created by Braeden on 9/3/2019.
//

#ifndef CRAWL_THE_DUNGEON_SOLDIER_H
#define CRAWL_THE_DUNGEON_SOLDIER_H

#include "Character.h"
#include "TilesEnum.cpp"
#include <cmath>

class Soldier {
public:
    bool attacked;
    int movement;
    int xPos;
    int yPos;

    Soldier(int x, int y);

    void attack(int positionX, int positionY, Character *mainChar);

    void move(int positionX, int positionY, int allTiles[34][60], Character *mainChar);

    bool moveR(int allTiles[34][60]);

    bool moveL(int allTiles[34][60]);

    bool moveU(int allTiles[34][60]);

    bool moveD(int allTiles[34][60]);

    void findNextMove(int positionX, int positionY, int allTiles[34][60], char lastCheck);

};


#endif //CRAWL_THE_DUNGEON_SOLDIER_H
