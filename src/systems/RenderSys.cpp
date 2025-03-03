//
// Created by seirar on 2/25/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL.h>

module RenderSys;

import Transform;
import Sprite;
import Camera;
import Collider;
import World;
import Animator;


void RenderSys::render(entt::registry &registry, SDL_Renderer *renderer) {
    auto view = registry.view<Transform, Sprite>();

    auto cameraView = registry.view<Camera>();
    auto cameraEnt = cameraView.front();
    auto& camera = cameraView.get<Camera>(cameraEnt);

    render_world(registry, renderer, cameraEnt);

    for (auto ent : view) {
        if (registry.all_of<Animator>(ent)) continue;
        auto [transform, sprite] = view.get(ent);

        SDL_FRect rect{
            0,
            0,
            transform.width,
            transform.height
        };

        rect.x = (transform.position.x - camera.viewport.x) * camera.zoom + camera.viewport.w / 2 - rect.w / 2;
        rect.y = (transform.position.y - camera.viewport.y) * camera.zoom + camera.viewport.h / 2 - rect.h / 2;

        SDL_RenderTexture(renderer, sprite.texture, nullptr, &rect);
        debug_collider(registry, renderer, &rect);
    }
}

void RenderSys::debug_collider(entt::registry &registry, SDL_Renderer *renderer, const SDL_FRect* rect_) {
    auto view = registry.view<Transform, Collider>();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (auto ent : view) {
        auto [transform, collider] = view.get(ent);

        SDL_FRect rect{
            collider.bounds.x + rect_->x,
            collider.bounds.y + rect_->y,
            collider.bounds.w,
            collider.bounds.h
        };

        SDL_RenderRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderSys::render_world(entt::registry &registry, SDL_Renderer *renderer, const entt::entity& camera_entity) {
    const auto map = World::current_map;

    auto& camera = registry.get<Camera>(camera_entity);

    float scale = camera.viewport.h / map->mapHeight;
    float scaledWidth = map->mapWidth * scale;

    const SDL_FRect rect {
        0, 0,
        static_cast<float>(map->texture->w) * camera.zoom,
        static_cast<float>(map->texture->h) * camera.zoom
    };

    const SDL_FRect render{
        -map->offsetX,
        0,
        scaledWidth,
        camera.viewport.h,
    };

    SDL_RenderTexture(renderer, map->texture, &rect, &render);

    if (map->debugWalkable) {
        SDL_FRect debug{
            -map->offsetX,
            0,
            scaledWidth,
            camera.viewport.h,
        };
        SDL_SetTextureBlendMode(map->debugWalkable, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(map->debugWalkable, 128); // 半透明
        SDL_RenderTexture(renderer, map->debugWalkable, nullptr, &debug);
    }
}
