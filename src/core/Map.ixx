//
// Created by seirar on 2/27/2025.
//
module;

#include <SDL3/SDL.h>
#include <string>

export module Map;

export struct Map {
    SDL_Texture* texture;
    SDL_Surface* walkableMask;
    SDL_Texture* debugWalkable;
    float mapWidth;
    float mapHeight;
    float offsetX;

    void load(SDL_Renderer* renderer, const std::string& texPath, const std::string& maskPath, const float& w,  const float& h);

    [[nodiscard]] bool is_walkable(float x, float y) const;
};