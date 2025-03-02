//
// Created by seirar on 3/2/2025.
//
module;

#include <string>
#include <entt/entity/registry.hpp>
#include <SDL3/SDL_render.h>

export module AnimationSys;

export namespace AnimationSys {
    void load_animations(entt::registry& registry, entt::entity entity, SDL_Renderer* renderer, const std::string& anim_name, const std::string& file);
    void update(entt::registry& registry, SDL_Renderer* renderer, float delta_time);
}