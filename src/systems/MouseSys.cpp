//
// Created by seirar on 2/27/2025.
//
module;

#include <entt/entt.hpp>
#include <SDL3/SDL_log.h>

module MouseSys;

import Input;
import Camera;

void MouseSys::update(entt::registry& registry, SDL_Event* event, const Map* map) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mouseX = Input::mouseX;
        float mouseY = Input::mouseY;

        auto cameraView = registry.view<Camera>();
        auto cameraEnt = cameraView.front();
        auto& camera = cameraView.get<Camera>(cameraEnt);

        float scale = camera.viewport.h / map->mapHeight;
        float scaledWidth = map->mapWidth * scale;
        float offsetX = (camera.viewport.w - scaledWidth) / 2.0f;

        float worldX = (mouseX - offsetX) / scale + map->offsetX;
        float worldY = mouseY / scale;

        int maskX = static_cast<int>(worldX * (map->walkableMask->w / map->mapWidth));
        int maskY = static_cast<int>(worldY * (map->walkableMask->h / map->mapHeight));

        if (map->is_walkable(maskX, maskY)) {
            SDL_Log("Clicked on walkable area at (%d, %d)", maskX, maskY);
        } else {
            SDL_Log("Clicked on non-walkable area at (%d, %d)", maskX, maskY);
        }
    }
}
