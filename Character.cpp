//Author: Braeden Lisowski
//Due Date: 5/06/2019
//Instructor: Alexi Brooks
//Final Project

class Character{ //main character class
    public:
    int health;//different stats
    int movement;
    Character(){
        health = 3; //starting health and movement
        movement = 1;
    }
    bool healthDown(){ //lowers the health stat
        health--;
        if(health == 0){ //when the health is at 0 return false to signal game over
            return false;
        }
        return true;
    }
    void healthUp(){ //up the health stat
        health++;
    }
    void movementUp(){ //up the movement stat
        movement++;
    }
    void movementDown(){ //lowers the movement stat
        if(movement == 1){ //you can not go below 1 movement so decrement health instead
            healthDown(); //will not end the game however
        }else{
            movement--; //lower movement
        }
    }
};






