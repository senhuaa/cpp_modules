//
// Created by seirar on 2/25/2025.
//
module;

#include <SDL3/SDL.h>

export module Sprite;

export struct Sprite {
    SDL_Texture* texture;
    float width;
    float height;
};
