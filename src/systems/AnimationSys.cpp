//
// Created by seirar on 3/2/2025.
//
module;

#include <iostream>
#include <memory>
#include <vector>
#include <entt/entt.hpp>
#include <SDL3_image/SDL_image.h>

module AnimationSys;

import Animator;
import Sprite;
import Transform;
import Camera;
import RenderSys;

void AnimationSys::load_animations(entt::registry& registry, entt::entity entity, SDL_Renderer* renderer, const std::string& anim_name, const std::string& file) {
    auto raw_anim = IMG_LoadAnimation(file.c_str());

    std::vector<SDL_Texture*> frames;
    for (int i = 0; i < raw_anim->count; ++i) {
        SDL_Surface* frame_surface = raw_anim->frames[i];
        SDL_Texture* frame_texture = SDL_CreateTextureFromSurface(renderer, frame_surface);
        if (!frame_texture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                "Failed to create texture for frame %d: %s",
                i, SDL_GetError()
            );

            IMG_FreeAnimation(raw_anim);
            return;
        }

        frames.emplace_back(frame_texture);
    }
    IMG_FreeAnimation(raw_anim);

    auto* anim_data = registry.try_get<Animator>(entity);
    if (!anim_data) {
        anim_data = &registry.emplace<Animator>(entity, "idle");
    }
    anim_data->animations[anim_name] = std::move(frames);
}

void AnimationSys::update(entt::registry& registry, SDL_Renderer* renderer, float delta_time) {
    auto view = registry.view<Animator, Sprite, Transform>();

    auto cameraView = registry.view<Camera>();
    auto cameraEnt = cameraView.front();
    auto& camera = cameraView.get<Camera>(cameraEnt);

    for (auto ent : view) {
        auto [animator, sprite, transform] = view.get(ent);

        auto animIt = animator.animations.find(animator.current_anim);
        if (animIt == animator.animations.end() || animIt->second.empty()) continue;

        auto& frames = animIt->second;

        animator.current_frame += animator.animation_speed * delta_time;
        if (static_cast<int>(animator.current_frame) >= frames.size()) {
            animator.current_frame = 0;
        }

        int frameIndex = static_cast<int>(animator.current_frame) % frames.size();
        SDL_Texture* frameTexture = frames[frameIndex];
        SDL_GetTextureSize(frameTexture, &transform.width, &transform.height);

        SDL_FRect destRect = {transform.position.x, transform.position.y, transform.width, transform.height};

        destRect.x = (transform.position.x - camera.viewport.x) * camera.zoom + camera.viewport.w / 2 - destRect.w / 2;
        destRect.y = (transform.position.y - camera.viewport.y) * camera.zoom + camera.viewport.h / 2 - destRect.h / 2;

        for (int i = 0; i < animator.animations.size(); ++i) {
            SDL_RenderTextureRotated(renderer, frameTexture, nullptr, &destRect, 0.0, nullptr, transform.flip);
        }
        //RenderSys::debug_collider(registry, renderer, &destRect);
    }
}
