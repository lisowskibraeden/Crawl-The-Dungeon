#include "Character.h"
//Author: Braeden Lisowski

Character::Character() {
    health = 3; //starting health and movement
    movement = 1;
}

void Character::healthDown() { //lowers the health stat
    health--;
    if (health <= 0) { //when the health is at 0 return false to signal game over
        dead = true;
    }
}

void Character::healthUp() { //up the health stat
    health++;
}

void Character::movementUp() { //up the movement stat
    movement++;
}

void Character::movementDown() { //lowers the movement stat
    if (movement == 1) { //you can not go below 1 movement so decrement health instead
        healthDown(); //will not end the game however
    } else {
        movement--; //lower movement
    }
}

