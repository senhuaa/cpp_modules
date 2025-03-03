//
// Created by seirar on 3/2/2025.
//
module;

#include <entt/entt.hpp>

export module PlayerStateMachine;

import Velocity;
import Transform;
import Animator;
import Camera;

export namespace PlayerStateMachine {
    void run(entt::registry& registry, float delta_time);
    void player_flip(Transform* tr);
    int play_walk(Velocity *vc, Transform *tr, Animator *am, const Camera* camera, const float delta_time);
}