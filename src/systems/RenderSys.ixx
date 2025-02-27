//
// Created by seirar on 2/25/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL.h>

export module RenderSys;

export namespace RenderSys {
    void render(entt::registry& registry, SDL_Renderer* renderer);
    void debug_collider(entt::registry& registry, SDL_Renderer* renderer);
    void render_world(entt::registry &registry, SDL_Renderer* renderer, const entt::entity& camera_entity);
}
