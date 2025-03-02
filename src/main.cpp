#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

import Window;
import Input;
import MouseSys;
import World;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    Window::create_window();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Window::tick_delta_time();
    Window::clear();
    Input::update();
    Window::render();
    Window::update();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    MouseSys::update(event, World::current_map);
    return event->type == SDL_EVENT_QUIT ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Quit();
}