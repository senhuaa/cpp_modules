//
// Created by seirar on 2/27/2025.
//
module;

#include <SDL3/SDL_log.h>

module MouseSys;

import Input;

void MouseSys::update(SDL_Event* event, const Map* map) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        float scale = 675.0f / static_cast<float>(map->walkableMask->h);
        float scaledWidth = map->walkableMask->w * scale;
        float startX = (1200.0f - scaledWidth) / 2.0f;

        float mapX = (mouseX - startX) / scale;
        float mapY = mouseY / scale;

        if (map->is_walkable(mapX, mapY)) {
            SDL_Log("clicked %f, %f", mapX, mapY);
        }
    }
}
