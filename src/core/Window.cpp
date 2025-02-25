//
// Created by seirar on 2/25/2025.
//
#include <stdexcept>
#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>
#include <SDL3/SDL.h>

import Window;
import Render;
import Transform;
import Sprite;
import Camera;

void Window::create_window(const int w, const int h) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(SDL_GetError());
    }

    window = SDL_CreateWindow("CPP MODULES", w, h, 0);
    renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Texture* a = nullptr;

    entt::entity rect = registry.create();
    registry.emplace<Transform>(rect, SDL_FPoint{100.0f, 200.0f}, 1000.0f, 200.0f);
    registry.emplace<Sprite>(rect, a, 100.0f, 100.0f);

    entt::entity camera = registry.create();
    registry.emplace<Camera>(camera, SDL_FRect{0.0f, 0.0f, 1600.0f, 960.0f});
}

void Window::update() {
    SDL_RenderPresent(renderer);
}

void Window::render() {
    Render::render(registry, renderer);
}

void Window::clear() {
    SDL_RenderClear(renderer);
}

void Window::tick_delta_time() {
    dt_last = dt_now;
    dt_now = SDL_GetTicks();
    delta_time = static_cast<float>(dt_now) - static_cast<float>(dt_last);
}
