//
// Created by seirar on 2/26/2025.
//
module;

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>

export module Input;

export struct Input {
    static const inline bool* state = SDL_GetKeyboardState(nullptr);

    static inline uint32_t mouseButtonState = 0;
    static inline float mouseX = 0.0f;
    static inline float mouseY = 0.0f;

    static void update() {
        mouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);
    }

    static void get_mouse_position(float& x, float& y) {
        x = mouseX;
        y = mouseY;
    }
};
