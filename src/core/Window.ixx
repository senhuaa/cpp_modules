//
// Created by seirar on 2/25/2025.
//
module;

#include <SDL3/SDL.h>

export module Window;

export struct Window {
    static inline SDL_Renderer* renderer;
    static inline SDL_Window* window;

    static void create_window(int w, int h);
};
