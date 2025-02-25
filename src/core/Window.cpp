//
// Created by seirar on 2/25/2025.
//
#include <stdexcept>
#include <SDL3/SDL.h>

import Window;

void Window::create_window(const int w, const int h) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(SDL_GetError());
    }

    window = SDL_CreateWindow("CPP MODULES", w, h, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
}
