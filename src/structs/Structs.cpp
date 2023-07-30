//
// Created by Braeden on 1/1/2020.
//

#include <SDL2/SDL_surface.h>

typedef struct { //struct to hold all surfaces
    SDL_Surface *surfaces[9];
    SDL_Surface *surfaceWithData;
    SDL_Surface *background;
} Surfaces;