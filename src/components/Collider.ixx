//
// Created by seirar on 2/26/2025.
//
module;

#include <SDL3/SDL_rect.h>

export module Collider;

export enum ColliderType {
    DYNAMIC,
    TILE
};

export struct Collider {
    SDL_FRect bounds;
    ColliderType type;
    bool isSolid;
};
