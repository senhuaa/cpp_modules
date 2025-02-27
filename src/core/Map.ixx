//
// Created by seirar on 2/27/2025.
//
module;

#include <SDL3/SDL.h>

export module Map;

export struct Map {
    SDL_Texture* texture;
    SDL_Surface* walkableMask;
};