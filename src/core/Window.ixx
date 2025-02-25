//
// Created by seirar on 2/25/2025.
//
module;

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

export module Window;

export struct Window {
    static inline SDL_Renderer* renderer;
    static inline SDL_Window* window;
    static inline entt::registry registry;

    static inline unsigned int dt_now = 0;
    static inline unsigned int dt_last = 0;
    static inline float delta_time = 0.0f;

    static void create_window(int w, int h);
    static void update();
    static void render();
    static void clear();
    static void tick_delta_time();
};
