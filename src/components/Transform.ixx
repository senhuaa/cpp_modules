//
// Created by seirar on 2/25/2025.
//
module;

#include <SDL3/SDL_rect.h>

export module Transform;

export struct Transform {
    SDL_FPoint position{};
    float width{};
    float height{};
};
