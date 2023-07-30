#ifndef CHARACTER_H
#define CHARACTER_H
#include "Entity.h"

class Character: public Entity {
    public:
        int movement;
        int health;
        int xPos;
        int yPos;
        void healthDown() {
            health--;
        }
};

#endif
