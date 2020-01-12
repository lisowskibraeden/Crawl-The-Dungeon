//
// Created by Braeden on 9/3/2019.
//

#ifndef CRAWL_THE_DUNGEON_CHARACTER_H
#define CRAWL_THE_DUNGEON_CHARACTER_H


//Author: Braeden Lisowski

class Character { //main character class
public:
    int health;//different stats
    int movement;
    bool dead = false;

    Character();

    void healthDown();

    void healthUp();

    void movementUp();

    void movementDown();
};


#endif //CRAWL_THE_DUNGEON_CHARACTER_H
