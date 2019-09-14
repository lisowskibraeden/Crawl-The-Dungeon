//
// Created by Braeden on 9/3/2019.
//

#include "Game.h"

Game::Game(SDL_Window *myWindow, SDL_Surface *surfaceWithData, SDL_Surface *background, int tileX, int tileY) {
    this->tileX = tileX;
    this->tileY = tileY;
    this->background = background;
    this->myWindow = myWindow;
    this->surfaceWithData = surfaceWithData;
    this->background = background;
    curSurface[BASIC_TILE] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/basictiles.png"); //load in all textures
    curSurface[LAVA_TILE] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/lava.png");
    curSurface[CHARACTER_TILE] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/mainChar.png");
    curSurface[HEALTH_ICON] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/heart.png");
    curSurface[ENEMY_TILE] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/slime.png");
    curSurface[LOOT_TILE] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/loot.png");
    curSurface[MOVEMENT_ICON] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/movement.png");
    curSurface[STAIRS_TILE] = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/stairs.png");
    srand(time(nullptr)); //make sure random works correctly
    for (int i = 0; i < 10; ++i) {
        for (int x = 0; x < 10; ++x) { //set up the maps
            allSurfaces[i][x] = (curSurface[allTiles[i][x]]);
        }
    }
}

bool Game::startGame() {
    mapMaker(allTiles);
    mainChar = Character();
    updateWindow();
    SDL_Event eventObject;
    while (!done) {
        while (SDL_PollEvent(&eventObject)) {
            if (eventObject.type == SDL_QUIT) {
                done = true;
            } else if (eventObject.type == SDL_KEYUP) {
                switch (eventObject.key.keysym.sym) {
                    case SDLK_UP:  //on left click
                        characterMove('U'); //try to move the player
                        break;
                    case SDLK_DOWN:
                        characterMove('D');
                        break;
                    case SDLK_RIGHT:
                        characterMove('R');
                        break;
                    case SDLK_LEFT:
                        characterMove('L');
                        break;
                }
            } else if (eventObject.type == SDL_KEYDOWN) {
                switch (eventObject.key.keysym.sym) {
                    case SDLK_RETURN: //on return click
                        nextTurn(); //send to next turn
                        break;
                }
            }
        }
    }
    return done;
}

void Game::nextFloor() { //send the player to the next floor
    mapMaker(allTiles);
    updateWindow();
    floorsTraveled++;
}

void Game::characterMove(char move) { //character turn to move
    int xTile = positionX; //finds what tile the player clicked on
    int yTile = positionY;
    switch (move) {
        case 'U':
            yTile--;
            break;
        case 'D':
            yTile++;
            break;
        case 'R':
            xTile++;
            break;
        case 'L':
            xTile--;
            break;
    }
    movesLeft--;
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
            for (auto &enemy : enemies) {
                if (enemy != nullptr) { //make sure there is an enemy to prevent null pointer
                    if (enemy->xPos == positionX &&
                        enemy->yPos == positionY) { //find which enemy died
                        (*enemy).attacked = true; //"delete" enemy by marking them attacked
                    }
                }
            }
            allTiles[positionY][positionX] = CHARACTER_TILE;
            updateWindow(); //make sure window updates
    }
    if (movesLeft <= 0) { //automatically set next turn when the player can not do anything else
        nextTurn();
    }
}

void Game::updateWindow() {
    SDL_Rect dest;
    dest.x = 0; //set up in the corner of the window
    dest.y = 0;
    SDL_BlitSurface(background, NULL, surfaceWithData, NULL); //reset background to clear screen
    dest.y = -1 * tileY;
    for (int i = 0; i < 34; ++i) { //run down rows
        dest.y = dest.y + tileY; //update each time
        dest.x = 0; //reset each time
        for (int x = 0; x < 60; ++x) { //run accross columns
            allSurfaces[i][x] = (curSurface[allTiles[i][x]]); //load in the texture for each tile
            printf(SDL_GetError());
            SDL_BlitSurface(allSurfaces[i][x], NULL, surfaceWithData, &dest); //add the texture to the window
            dest.x = dest.x + tileX; //increment x to go across columns

        }
    }
    updateHealth(); //display health
    updateMovement(); //display movement
    SDL_UpdateWindowSurface(myWindow); //finally send to window
}

void Game::loot() { //player gains loot
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

void Game::updateMovement() { //displays character movement stat
    SDL_Rect dest;
    dest.x = 1000; //location for the movement icons to display
    dest.y = 700;
    for (int i = 0; i < mainChar.movement; i++) { //add in for each icon
        SDL_BlitSurface((curSurface[MOVEMENT_ICON]), NULL, surfaceWithData, &dest);
        dest.x = dest.x - 20; //move across columns to display each icon
    }
}

void Game::updateHealth() { //displays the character health stat
    SDL_Rect dest;
    dest.x = 0; //location for the health icon to display
    dest.y = 685;
    for (int i = 0; i < mainChar.health; i++) { //run fo reach health value
        SDL_BlitSurface((curSurface[HEALTH_ICON]), NULL, surfaceWithData, &dest);
        dest.x = dest.x + 35; //go across to display all health
    }
}

void Game::nextTurn() { //ends character turn and allows enemies to move
    movesLeft = mainChar.movement;
    enemyMove();
}

void Game::enemyMove() { //makes all enemies move
    for (auto &enemy : enemies) {
        if (enemy != nullptr) {
            if (abs(enemy->xPos - positionX) < 7 && abs(enemy->yPos - positionY) < 7) {
                (*enemy).move(positionX, positionY, allTiles,
                              &mainChar); //allows the enmies to move around and attack
            }
        }
    }
    updateWindow();
    if (mainChar.dead) {
        gameOver();
    }
}

void Game::gameOver() { //when the player dies (no health or movement (can not die from loot))
    updateWindow();
    string endMessage = "You died! You made it to: "; //construct death message
    endMessage += to_string(floorsTraveled);
    endMessage += " floor(s)";
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", endMessage.c_str(), NULL); //display the message
    done = true;
}

void Game::mapMaker(int tileMap[34][60]) {
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
}
