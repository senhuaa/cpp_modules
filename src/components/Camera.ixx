//
// Created by seirar on 2/25/2025.
//
module;

#include <SDL3/SDL_rect.h>

export module Camera;

export struct Camera {
    SDL_FRect viewport;
    float zoom;
};
