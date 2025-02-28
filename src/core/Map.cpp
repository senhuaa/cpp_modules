//
// Created by seirar on 2/27/2025.
//
module;

#include <SDL3/SDL.h>
#include <string>
#include <stdexcept>

#include <SDL3_image/SDL_image.h>

module Map;

import Window;


void Map::load(SDL_Renderer* renderer, const std::string& texPath, const std::string& maskPath, const float& w,  const float& h) {
    texture = IMG_LoadTexture(renderer, texPath.c_str());
    if (!texture) {
        throw std::runtime_error(SDL_GetError());
    }
    walkableMask = SDL_LoadBMP(maskPath.c_str());
    mapWidth = w;
    mapHeight = h;
    offsetX = 0.0f;
}

bool Map::is_walkable(const float x, const float y) const {
    if (!walkableMask) return false;

    int pixelX = static_cast<int>(x);
    int pixelY = static_cast<int>(y);

    if (pixelX < 0 || pixelX >= walkableMask->w ||
        pixelY < 0 || pixelY >= walkableMask->h) {
        return false;
        }

    const Uint32* pixels = static_cast<Uint32*>(walkableMask->pixels);
    Uint32 pixel = pixels[pixelY * walkableMask->pitch / sizeof(Uint32) + pixelX];

    return (pixel & 0x00FFFFFF) != 0;
}
