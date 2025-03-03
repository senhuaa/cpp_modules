//
// Created by seirar on 2/27/2025.
//
module;

#include <iostream>
#include <ostream>
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

    debugWalkable = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, walkableMask->w, walkableMask->h);
    Uint8* pixels;
    int pitch;
    SDL_LockTexture(debugWalkable, nullptr, reinterpret_cast<void **>(&pixels), &pitch);
    if (!walkableMask) return;
    const auto* maskPixels = static_cast<Uint8 *>(walkableMask->pixels);
    int bytesPerPixel = 3;
    int rowSize = walkableMask->pitch / bytesPerPixel;
    for (int y = 0; y < walkableMask->h; y++) {
        for (int x = 0; x < walkableMask->w; x++) {
            int index = y * walkableMask->pitch + x * bytesPerPixel;

            Uint8 r = maskPixels[index];
            Uint8 g = maskPixels[index + 1];
            Uint8 b = maskPixels[index + 2];

            Uint8 grayscale = (r + g + b) / 3;
            bool walkable = grayscale > 128;

            int targetIndex = y * pitch + x * 4;
            pixels[targetIndex] = walkable ? 0 : 255;       // R
            pixels[targetIndex + 1] = walkable ? 255 : 0;   // G
            pixels[targetIndex + 2] = 0;                    // B
            pixels[targetIndex + 3] = 255;                  // A
        }
    }
    SDL_UnlockTexture(debugWalkable);

    mapWidth = w;
    mapHeight = h;
    offsetX = 0.0f;
}

bool Map::is_walkable(const float x, const float y) const {
    if (!walkableMask) return false;

    float scale = static_cast<float>(walkableMask->h) / mapHeight;

    int pixelX = static_cast<int>((x + offsetX) * scale);
    int pixelY = static_cast<int>(y * scale);

    if (pixelX < 0 || pixelX >= walkableMask->w ||
        pixelY < 0 || pixelY >= walkableMask->h) {
        return false;
        }

    auto pixels = static_cast<const Uint8*>(walkableMask->pixels);
    int bytesPerPixel = 3;
    int index = pixelY * walkableMask->pitch + pixelX * bytesPerPixel;

    Uint8 r = pixels[index];
    Uint8 g = pixels[index + 1];
    Uint8 b = pixels[index + 2];

    Uint8 grayscale = (r + g + b) / 3;

    return grayscale > 128;
}
