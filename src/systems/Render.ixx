//
// Created by seirar on 2/25/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL.h>

export module Render;

export namespace Render {
    void render(entt::registry& registry, SDL_Renderer* renderer);
}
