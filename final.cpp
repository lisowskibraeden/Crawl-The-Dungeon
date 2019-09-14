//Author: Braeden Lisowski
//Crawl The Dungeon mega file
#include <iostream>
#include "Game.h"
//enum to keep track of which value corresponds with each tile type
const int windowHeight = 720;
const int windowWidth = 1280;
const int tileX = 20; //the x length of tiles
const int tileY = 20; //the y length of tiles
SDL_Window *myWindow = nullptr;
SDL_Surface *curSurface[9]; //an vector of all loaded surfaces
SDL_Surface *surfaceWithData = nullptr;
SDL_Surface *background;
SDL_Surface *menu;

void refreshMenu();

void showHighScore();

void startup();

void makeMenu();

void startGame();

void startMenu();

bool done = false;
using namespace std;

int main(int argv, char *args[]) {
    startup();
}

void startMenu() {
    int x;
    int y;
    SDL_Event eventObject;
    refreshMenu();
    while (!done) {
        while (SDL_PollEvent(&eventObject)) {
            if (eventObject.type == SDL_QUIT) {
                done = true;
            } else if (eventObject.type == SDL_MOUSEBUTTONDOWN) {
                switch (eventObject.button.button) {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&x, &y);
                        if (x >= 575 && x <= 700 && y >= 215 && y <= 270) {
                            startGame();
                            refreshMenu();
                        } else if (x >= 575 && x <= 700 && y >= 215 && y <= 270) {
                            showHighScore();
                        }
                        break;
                }
            }
        }
    }
}

void refreshMenu() {
    SDL_BlitSurface(menu, nullptr, surfaceWithData, nullptr);
    SDL_UpdateWindowSurface(myWindow);
}

void makeMenu() {
    cout << "HELLO" << endl;
    SDL_Surface *mainText;
    SDL_Surface *startText;
    menu = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/background.png");;
    startText = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/startText.png");
    mainText = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/mainText.png");
    SDL_Rect rect;
    rect.x = (windowWidth - mainText->w) / 2;
    rect.y = 10;
    SDL_BlitSurface(mainText, NULL, menu, &rect);
    rect.x = (windowWidth - startText->w) / 2;
    rect.y = 200;
    SDL_BlitSurface(startText, nullptr, menu, &rect);
}

void startGame() {
    Game *game = new Game(myWindow, surfaceWithData, background, tileX, tileY);
    game->startGame();
    delete (game);
}

void showHighScore() {

}

void startup() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "panic sdl failed";
        exit(1);
    }
    IMG_Init(IMG_INIT_PNG);
    myWindow = SDL_CreateWindow("Crawl the Dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);//the main window
    surfaceWithData = SDL_GetWindowSurface(myWindow);
    background = IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/background.png");
    SDL_SetWindowIcon(myWindow, IMG_Load("C:/Users/Braeden/repos/Crawl-The-Dungeon/resources/mainChar.png"));
    makeMenu();
    startMenu();

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
    SDL_FreeSurface(curSurface[8]);
    SDL_FreeSurface(background);
    SDL_FreeSurface(menu);
    SDL_DestroyWindow(myWindow);
    SDL_Quit();
}
