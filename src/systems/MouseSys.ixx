//
// Created by seirar on 2/27/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL_events.h>

export module MouseSys;

import Map;

export namespace MouseSys {
    void update(entt::registry& registry, SDL_Event* event, const Map* map);
}
