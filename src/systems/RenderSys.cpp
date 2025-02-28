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


void RenderSys::render(entt::registry &registry, SDL_Renderer *renderer) {
    auto view = registry.view<Transform, Sprite>();

    auto cameraView = registry.view<Camera>();
    auto cameraEnt = cameraView.front();
    auto& camera = cameraView.get<Camera>(cameraEnt);

    for (auto ent : view) {
        auto [transform, sprite] = view.get(ent);

        SDL_FRect rect{
            transform.position.x * camera.zoom,
            transform.position.y * camera.zoom,
            transform.width,
            transform.height
        };

        rect.x = (transform.position.x - camera.viewport.x) * camera.zoom + camera.viewport.w / 2 - rect.w / 2;
        rect.y = (transform.position.y - camera.viewport.y) * camera.zoom + camera.viewport.h / 2 - rect.h / 2;

        SDL_RenderTexture(renderer, sprite.texture, &rect, nullptr);
    }
    //debug_collider(registry, renderer);
    render_world(registry, renderer, cameraEnt);
}



void RenderSys::debug_collider(entt::registry &registry, SDL_Renderer *renderer) {
    auto view = registry.view<Transform, Collider>();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (auto ent : view) {
        auto [transform, collider] = view.get(ent);

        SDL_FRect rect{
            collider.bounds.x + transform.position.x,
            collider.bounds.y + transform.position.y,
            collider.bounds.w,
            collider.bounds.h
        };

        SDL_RenderRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderSys::render_world(entt::registry &registry, SDL_Renderer *renderer, const entt::entity& camera_entity) {
    const auto map = World::current_world;

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
}
