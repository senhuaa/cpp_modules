#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

import Window;
import Input;

static constexpr int WIDTH = 1600;
static constexpr int HEIGHT = 960;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    Window::create_window(WIDTH, HEIGHT);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Window::tick_delta_time();
    Input::update_mouse_state();
    Window::clear();
    Window::render();
    Window::update();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    return (event->type == SDL_EVENT_QUIT) ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Quit();
}