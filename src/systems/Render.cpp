//
// Created by seirar on 2/25/2025.
//
#include <entt/entt.hpp>
#include <SDL3/SDL.h>

module Render;
import Transform;
import Sprite;
import Camera;


void Render::render(entt::registry &registry, SDL_Renderer *renderer) {
    auto view = registry.view<Transform, Sprite>();

    auto cameraView = registry.view<Camera>();
    auto cameraEnt = cameraView.front();
    auto& camera = cameraView.get<Camera>(cameraEnt);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (auto ent : view) {
        auto [transform, sprite] = view.get(ent);

        SDL_FRect rect{
            transform.position.x,
            transform.position.y,
            transform.width,
            transform.height
        };

        //rect.x = (transform.position.x - camera.viewport.x) * camera.zoom + camera.viewport.w / 2 - rect.w / 2;
        //rect.y = (transform.position.y - camera.viewport.y) * camera.zoom + camera.viewport.h / 2 - rect.h / 2;

        //SDL_RenderTexture(renderer, sprite.texture, &rect, nullptr);
        SDL_RenderRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
