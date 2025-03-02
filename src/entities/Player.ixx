//
// Created by seirar on 3/2/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL_render.h>

export module Player;

export namespace Player {
    void create_player(entt::registry& registry, SDL_Renderer* renderer);
}