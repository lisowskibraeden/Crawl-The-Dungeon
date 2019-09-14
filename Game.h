#ifndef CRAWL_THE_DUNGEON_GAME_H
#define CRAWL_THE_DUNGEON_GAME_H

#include "Character.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Soldier.h"
#include "Room_List.cpp"
#include <ctime>
#include <unordered_map>
using namespace std;

class Game {
private:

    bool done = false;
    int tileX;
    int tileY;
    SDL_Window *myWindow = nullptr;
    int allTiles[34][60]; //an array of all the surface values corresponding with the enum tiles
    SDL_Surface *allSurfaces[34][60]; //an array of all the surfaces
    SDL_Surface *curSurface[9]; //an array of all loaded surfaces
    SDL_Surface *surfaceWithData = nullptr;
    SDL_Surface *background;
    int movesLeft = mainChar.movement; //how many moves left in the current turn
    int positionX = 1; //position (x) of the character
    int positionY = 1; //position (y) of the character
    Character mainChar; //the main character
    Soldier *enemies[10]; //all of the enemies
    int floorsTraveled = 1; //how many floors traveled

    void nextFloor();

    void characterMove(char move);

    void loot();

    void updateMovement();

    void updateHealth();

    void nextTurn();

    void enemyMove();

    void gameOver();

    void mapMaker(int tileMap[34][60]);

    void updateWindow();

public:
    bool startGame();

    Game(SDL_Window *myWindow, SDL_Surface *surfaceWithData, SDL_Surface *background, int tileX, int tileY);
};


#endif //CRAWL_THE_DUNGEON_GAME_H
