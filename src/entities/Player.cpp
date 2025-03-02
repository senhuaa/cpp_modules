//
// Created by seirar on 3/2/2025.
//
module;

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <entt/entt.hpp>

module Player;

import Sprite;
import Transform;
import Collider;
import Character;
import AnimationSys;
import Animator;


void Player::create_player(entt::registry &registry, SDL_Renderer* renderer) {
    auto ent = registry.create();

    float w, h;
    SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/player/4.png");
    SDL_GetTextureSize(texture, &w, &h);

    registry.emplace<Character>(ent);
    registry.emplace<Sprite>(ent, texture, w, h);
    registry.emplace<Transform>(ent, SDL_FPoint{20.0f, 100.0f}, w, h);
    registry.emplace<Collider>(ent, SDL_FRect{0.0f, 0.0f, w, h}, ColliderType::DYNAMIC, true);
    AnimationSys::load_animations(registry, ent, renderer, "run", "assets/player/run.gif");
}
