//
// Created by seirar on 2/25/2025.
//
module;

#include <stdexcept>
#include <entt/entity/registry.hpp>
#include <SDL3/SDL.h>

module Window;
import RenderSys;
import Transform;
import Sprite;
import Camera;

void Window::create_window(const int w, const int h) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(SDL_GetError());
    }

    window = SDL_CreateWindow("CPP MODULES", w, h, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
}

void Window::update() {
    SDL_RenderPresent(renderer);
}

void Window::render() {
    //RenderSys::render(registry, renderer);
}

void Window::clear() {
    SDL_RenderClear(renderer);
}

void Window::tick_delta_time() {
    dt_last = dt_now;
    dt_now = SDL_GetTicks();
    delta_time = static_cast<float>(dt_now) - static_cast<float>(dt_last);
}
