//
// Created by seirar on 2/27/2025.
//
module;

#include <SDL3/SDL_log.h>

module MouseSys;

void MouseSys::update(SDL_Event* event, const Map* map) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        float scale = static_cast<float>(map->walkableMask->h) / 675.0f;
        float scaledWidth = 2801.0f * scale;
        float startX = (1200.0f - scaledWidth) / 2.0f; // 居中后的起始 x 坐标

        float mapX = (mouseX - startX) / scale;
        float mapY = mouseY / scale;

        if (map->is_walkable(mapX, mapY)) {
            SDL_Log("clicked");
        }
    }
}
