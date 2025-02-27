//
// Created by seirar on 2/27/2025.
//
module;

#include <entt/entt.hpp>

export module World;


export struct World {
    static inline auto registry = new entt::registry{};
};
