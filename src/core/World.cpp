//
// Created by seirar on 2/27/2025.
//
module;

#include <SDL3/SDL_stdinc.h>
#include <chrono>

module World;

import Input;

void World::load_world() {
    if (!map_list.empty()) {
        current_world = map_list[0];
    }
}

void World::load_maps(SDL_Renderer* renderer) {
    auto huanlejiedong = new Map();
    huanlejiedong->load(renderer, "assets/map/huanlejiedong.png", "assets/map/huanlejiedong_mask.bmp", 2801.0f, 676.0f);
    map_list.emplace(0, huanlejiedong);
}

void World::update(int w, int h, float delta_time) {
    constexpr float edgeThreshold = 50.0f;

    if (Input::mouseX >= static_cast<float>(w) - edgeThreshold) {
        current_world->offsetX += 1.0f * delta_time;
    } else if (Input::mouseX <= edgeThreshold) {
        current_world->offsetX -= 1.0f * delta_time;
    }

    const float mapOffsetX = current_world->mapWidth - static_cast<float>(w) - 4.5f;
    current_world->offsetX = std::floor(SDL_clamp(current_world->offsetX, 0.0f, mapOffsetX));
}
