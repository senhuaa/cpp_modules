//
// Created by seirar on 3/2/2025.
//
module;

#include <memory>
#include <string>
#include <unordered_map>
#include <SDL3_image/SDL_image.h>

export module Animator;

export struct Animator {
    std::string current_anim;
    std::unordered_map<std::string, std::vector<SDL_Texture*>> animations;
    float current_frame{0};
    float animation_speed = 1.0f;

    void play(const std::string& name) {
        if (animations.contains(current_anim) && current_anim != name) {
            current_anim = name;
            current_frame = 0;
        }
    }
};