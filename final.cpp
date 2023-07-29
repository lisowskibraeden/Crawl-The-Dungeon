//Author: Braeden Lisowski
//Crawl The Dungeon mega file
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include "./Map_Gen/Room_List.cpp"
#include "Entities/Soldier.cpp"
#include "Entities/Main_Character.cpp"
//enum to keep track of which value corresponds with each tile type

const int tileX = 20; //the x length of tiles
const int tileY = 20; //the y length of tiles
SDL_Window *myWindow = NULL;
int allTiles[34][60]; //an array of all the surface values corresponding with the enum tiles
SDL_Surface *allSurfaces[34][60]; //an array of all the surfaces
SDL_Surface *curSurface[9]; //an array of all loaded surfaces
SDL_Surface *surfaceWithData = NULL;
SDL_Surface *background;
int positionX = 1; //position (x) of the character
int positionY = 1; //position (y) of the character
Main_Character mainChar; //the main character
int movesLeft = mainChar.movement; //how many moves left in the current turn
Soldier *enemies[10]; //all of the enemies
int floorsTraveled = 1; //how many floors traveled

void nextFloor();

void updateMovement();

void mapMaker(int tileMap[][60]);

void quit();

void gameOver();

void nextTurn();

void enemyMove();

void startup();

void characterMove(int x, int y);

void nextFloor();

void loot();

void updateWindow();

void updateHealth();

bool done = false;
using namespace std;

int main(int argv, char *args[]) {
    //initializations
    int x;
    int y;
    mapMaker(allTiles);
    startup();
    //event loop
    SDL_Event eventObject;
    while (!done) {
        while (SDL_PollEvent(&eventObject)) {
            if (eventObject.type == SDL_QUIT) {
                done = true;
            } else if (eventObject.type == SDL_MOUSEBUTTONDOWN) {
                switch (eventObject.button.button) {
                    case SDL_BUTTON_LEFT:  //on left click
                        SDL_GetMouseState(&x, &y);
                        characterMove(x, y); //try to move the player
                        break;
                }
            } else if (eventObject.type == SDL_KEYDOWN) {
                switch (eventObject.key.keysym.sym) {
                    case SDLK_RETURN: //on return click
                        nextTurn(); //send to next turn
                        break;
                }
            } else if (eventObject.window.event == SDL_WINDOWEVENT_EXPOSED) {
                updateWindow();
            }
        }
    }
    quit();
}

void nextFloor() { //send the player to the next floor
    mapMaker(allTiles);
    updateWindow();
    floorsTraveled++;
}

void characterMove(int x, int y) { //character turn to move
    int xTile = x / tileX; //finds what tile the player clicked on
    int yTile = y / tileY;
    if (((abs((yTile - positionY)) <= movesLeft) && ((xTile - positionX) == 0)) ||
        ((abs((xTile - positionX)) <= movesLeft) &&
         ((yTile - positionY) == 0))) { //checks to see if the player clicked on a tile they can move to
        if (xTile == positionX && yTile == positionY) { //you can not move to your own tile (hit return to end turn)
            //do nothing
        } else {
            movesLeft -= abs((yTile - positionY));
            movesLeft -= abs((xTile - positionX));
            switch (allTiles[yTile][xTile]) {

                case BASIC_TILE: //when moving to a basic tile
                    allTiles[positionY][positionX] = BASIC_TILE; //reset previous tile
                    positionX = xTile; //change position
                    positionY = yTile;
                    allTiles[positionY][positionX] = CHARACTER_TILE; //place character at new tile
                    updateWindow(); //update to user
                    break;
                case LAVA_TILE: //when "moving" to a lava tile
                    break; //you can't move onto lava
                case STAIRS_TILE: //when moving to a stairs tile
                    nextFloor(); //send player to the next floor
                    break;
                case LOOT_TILE: //when moving to a loot tile
                    allTiles[positionY][positionX] = BASIC_TILE; //replace old tile
                    positionX = xTile; //set new position
                    positionY = yTile;
                    allTiles[positionY][positionX] = CHARACTER_TILE; //set player to new tile
                    loot(); //give player loot
                    updateWindow(); //update to user
                    break;
                case ENEMY_TILE: //when moving to an enemy tile
                    allTiles[positionY][positionX] = BASIC_TILE; //reset old tile
                    positionX = xTile; //set new position
                    positionY = yTile;
                    for (int i = 0; i < 10; i++) {
                        if (enemies[i] != NULL) { //make sure there is an enemy to prevent null pointer
                            if (enemies[i]->xPos == positionX &&
                                enemies[i]->yPos == positionY) { //find which enemy died
                                (*enemies[i]).attacked = true; //"delete" enemy by marking them attacked
                            }
                        }
                    }
                    allTiles[positionY][positionX] = CHARACTER_TILE;
                    updateWindow(); //make sure window updates
            }
            if (movesLeft == 0) { //automatically set next turn when the player can not do anything else
                nextTurn();
            }
        }
    }
    //enemyMove();
}

void startup() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "panic sdl failed";
        exit(1);
    }
    IMG_Init(IMG_INIT_PNG);
    myWindow = SDL_CreateWindow("Crawl the Dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);//the main window
    surfaceWithData = SDL_GetWindowSurface(myWindow);
    curSurface[BASIC_TILE] = IMG_Load("./resources/basictiles.png"); //load in all textures
    curSurface[LAVA_TILE] = IMG_Load("./resources/lava.png");
    curSurface[CHARACTER_TILE] = IMG_Load("./resources/mainChar.png");
    curSurface[HEALTH_ICON] = IMG_Load("./resources/heart.png");
    curSurface[ENEMY_TILE] = IMG_Load("./resources/slime.png");
    curSurface[LOOT_TILE] = IMG_Load("./resources/loot.png");
    background = IMG_Load("./resources/background.png");
    curSurface[MOVEMENT_ICON] = IMG_Load("./resources/movement.png");
    curSurface[STAIRS_TILE] = IMG_Load("./resources/stairs.png");
    SDL_SetWindowIcon(myWindow, curSurface[CHARACTER_TILE]);
    srand(time(NULL)); //make sure random works correctly

    for (int i = 0; i < 10; ++i) {
        for (int x = 0; x < 10; ++x) { //set up the maps
            allSurfaces[i][x] = curSurface[allTiles[i][x]];
        }
    }
    updateWindow();
}

void updateWindow() {
    SDL_Rect dest;
    dest.x = 0; //set up in the corner of the window
    dest.y = 0;
    SDL_BlitSurface(background, NULL, surfaceWithData, NULL); //reset background to clear screen
    SDL_BlitSurface(background, NULL, surfaceWithData, &dest); //reset background to clear screen
    dest.y = -1 * tileY;
    for (int i = 0; i < 34; ++i) { //run down rows
        dest.y = dest.y + tileY; //update each time
        dest.x = 0; //reset each time
        for (int x = 0; x < 60; ++x) { //run accross columns
            allSurfaces[i][x] = curSurface[allTiles[i][x]]; //load in the texture for each tile
            if(allSurfaces[i][x] == 0) {
                dest.x = dest.x + tileX;
                continue;
            } else if (allTiles[i][x] == CHARACTER_TILE || allTiles[i][x] == ENEMY_TILE || allTiles[i][x] == LOOT_TILE) {
                SDL_BlitSurface(curSurface[BASIC_TILE], NULL, surfaceWithData, &dest);
            }
            SDL_BlitSurface(allSurfaces[i][x], NULL, surfaceWithData, &dest); //add the texture to the window
            dest.x = dest.x + tileX; //increment x to go across columns
        }
    }
    updateHealth(); //display health
    updateMovement(); //display movement
    SDL_UpdateWindowSurface(myWindow); //finally send to window
}

void loot() { //player gains loot
    if (((rand()) % 100) > 10) { //1/10 chance the loot is bad
        switch (rand() % 2) { //1/2 chance for either health or movement up
            case 0:
                mainChar.healthUp();
                break;
            case 1:
                mainChar.movementUp();
                break;
        }
    } else {
        switch (rand() % 2) { //1/2 chance for health or movement down
            case 0:
                mainChar.healthDown();
                break;
            case 1:
                mainChar.movementDown();
                break;
        }
    }
}

void updateMovement() { //displays character movement stat
    SDL_Rect dest;
    dest.x = 1000; //location for the movement icons to display
    dest.y = 700;
    for (int i = 0; i < mainChar.movement; i++) { //add in for each icon
        SDL_BlitSurface(curSurface[MOVEMENT_ICON], NULL, surfaceWithData, &dest);
        dest.x = dest.x - 20; //move across columns to display each icon
    }
}

void updateHealth() { //displays the character health stat
    SDL_Rect dest;
    dest.x = 0; //loaction for the health icon to display
    dest.y = 685;
    for (int i = 0; i < mainChar.health; i++) { //run fo reach health value
        SDL_BlitSurface(curSurface[HEALTH_ICON], NULL, surfaceWithData, &dest);
        dest.x = dest.x + 35; //go across to display all health
    }
}

void nextTurn() { //ends character turn and allows enemies to move
    movesLeft = mainChar.movement;
    enemyMove();
}

void enemyMove() { //makes all enemies move
    for (int i = 0; i < 10; i++) {
        if (enemies[i] != NULL) {
            if (abs(enemies[i]->xPos - positionX) < 7 && abs(enemies[i]->yPos - positionY) < 7) {
                (*enemies[i]).move(positionX, positionY, allTiles, &mainChar); //allows the enmies to move around and attack
            }
        }
    }
    updateWindow();
    if (mainChar.dead) {
        gameOver();
    }
}

void quit() {
    SDL_FreeSurface(curSurface[0]); //free all the surfaces
    SDL_FreeSurface(curSurface[1]);
    SDL_FreeSurface(curSurface[2]);
    SDL_FreeSurface(curSurface[3]);
    SDL_FreeSurface(curSurface[4]);
    SDL_FreeSurface(curSurface[5]);
    SDL_FreeSurface(curSurface[6]);
    SDL_FreeSurface(curSurface[7]);
    SDL_FreeSurface(surfaceWithData);
    SDL_DestroyWindow(myWindow);
    SDL_Quit();
}

void gameOver() { //when the player dies (no health or movement (can not die from loot))
    updateWindow();
    string endMessage = "You died! You made it to: "; //construct death message
    endMessage += to_string(floorsTraveled);
    endMessage += " floor(s)";

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", endMessage.c_str(), NULL); //display the message
    done = true; //end the event loop to end the game
}

void mapMaker(int tileMap[34][60]) {
    Room_List roomStorage; // object of Room_List used to access the 3D array within "Room_List.cpp"


    int randIndex; // picks a random room from the 3D array in Room_List.cpp

    // for loop to fill the first and then the second row of the map array
    for (int rows = 0; rows < 2; rows++) {
        // for loop to fill the columns of each row from left to right
        for (int columns = 0; columns < 3; columns++) {
            // creates a random number to choose a random room from the array in Room_List.cpp
            randIndex = rand() % 9;

            // for loop to fill each row in a row/space
            for (int miniRows = 0 + (rows * 17); miniRows < 17 + (rows * 17); miniRows++) {
                // for loop to fill each element in a row of a room/space
                for (int miniColumns = 0 + (columns * 20); miniColumns < 20 + (columns * 20);
                     miniColumns++) {
                    // adds the premade rooms to certain locations of the tileMap
                    tileMap[miniRows][miniColumns] = roomStorage.listOfRooms[randIndex][miniRows -
                                                                                        (rows * 17)][miniColumns -
                                                                                                     (columns * 20)];
                }
            }
        }
    }

    //creates 4 horizontal tunnels to connect the rooms
    for (int horizPathLevel = 0; horizPathLevel < 2; horizPathLevel++) {
        for (int horizPathSides = 0; horizPathSides < 2; horizPathSides++) {
            for (int horizPathY = 0; horizPathY < 2; horizPathY++) {
                for (int horizPathX = 0; horizPathX < 6; horizPathX++) {
                    tileMap[8 + horizPathY + (horizPathLevel * 17)][17 + horizPathX +
                                                                    (horizPathSides * 20)] = 1;
                }
            }
        }
    }

    //creates 3 vertical tunnels to connect the rooms
    for (int vertiPathColumn = 0; vertiPathColumn < 3; vertiPathColumn++) {
        for (int vertiPathY = 0; vertiPathY < 6; vertiPathY++) {
            for (int vertiPathX = 0; vertiPathX < 2; vertiPathX++) {
                tileMap[16 + vertiPathY][9 + vertiPathX + (vertiPathColumn * 20)] = 1;
            }
        }
    }

    int numOfStairs = 1; // number of stairs per level
    int numOfSpawns = 1; // number of player spawns per level
    int numOfEnemies = 10;
    int numOfLoot = 10; // number of loot items per level

    int randomCoordX; //stores a random x coordinate on the map
    int randomCoordY; //stores a random y coordinate on the map

    //adds stairs to the map
    while (numOfStairs != 0) {
        randomCoordX = rand() % 60;
        randomCoordY = rand() % 34;

        if (tileMap[randomCoordY][randomCoordX] != 0 &&
            tileMap[randomCoordY][randomCoordX] != 2) {

            tileMap[randomCoordY][randomCoordX] = 3;
            numOfStairs--;
        }
    }

    //adds player spawns to the map
    while (numOfSpawns != 0) {
        randomCoordX = rand() % 60;
        randomCoordY = rand() % 34;

        if (tileMap[randomCoordY][randomCoordX] != 0 &&
            tileMap[randomCoordY][randomCoordX] != 2 &&
            tileMap[randomCoordY][randomCoordX] != 3) {

            tileMap[randomCoordY][randomCoordX] = 4;
            positionX = randomCoordX;
            positionY = randomCoordY;
            numOfSpawns--;
        }
    }

    //adds enemy spawns to the map
    while (numOfEnemies != 0) {
        randomCoordX = rand() % 60;
        randomCoordY = rand() % 34;

        if (tileMap[randomCoordY][randomCoordX] != 0 &&
            tileMap[randomCoordY][randomCoordX] != 2 &&
            tileMap[randomCoordY][randomCoordX] != 3 &&
            tileMap[randomCoordY][randomCoordX] != 4) {

            tileMap[randomCoordY][randomCoordX] = 5;

            numOfEnemies--;
            enemies[numOfEnemies] = new Soldier(randomCoordX, randomCoordY);
        }
    }

    //adds loot to the map
    while (numOfLoot != 0) {
        randomCoordX = rand() % 60;
        randomCoordY = rand() % 34;

        if (tileMap[randomCoordY][randomCoordX] != 0 &&
            tileMap[randomCoordY][randomCoordX] != 2 &&
            tileMap[randomCoordY][randomCoordX] != 3 &&
            tileMap[randomCoordY][randomCoordX] != 4 &&
            tileMap[randomCoordY][randomCoordX] != 5) {

            tileMap[randomCoordY][randomCoordX] = 6;
            numOfLoot--;
        }
    }

};
