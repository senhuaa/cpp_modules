//
// Created by seirar on 2/27/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <unordered_map>

export module World;

import Map;

export struct World {
    static inline auto registry = new entt::registry{};
    static inline std::unordered_map<unsigned int, Map*> map_list{};
    static inline Map* current_map{};

    static void load_world();
    static void load_maps(SDL_Renderer* renderer);
    static void update(entt::registry& registry, int w, int h, float delta_time);
};
