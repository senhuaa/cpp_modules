//
// Created by seirar on 2/25/2025.
//
module;

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_surface.h>

export module Transform;

import World;

export struct Transform {
    SDL_FPoint position;
    float width;
    float height;
    SDL_FlipMode flip;

    static void to_world_position(Transform* tr, float* x, float* y) {
        const auto map = World::current_map;

        float scale = 675.0f / static_cast<float>(map->walkableMask->h);
        float scaledWidth = map->walkableMask->w * scale;
        float startX = (1200.0f - scaledWidth) / 2.0f;

        *x = (tr->position.x - startX) / scale;
        *y = tr->position.y / scale;
    }
};
