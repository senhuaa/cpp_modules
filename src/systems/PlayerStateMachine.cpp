//
// Created by seirar on 3/2/2025.
//
module;

#include <iostream>
#include <entt/entt.hpp>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_surface.h>

module PlayerStateMachine;

import Velocity;
import Transform;
import Animator;
import Character;
import Input;
import World;
import Camera;

void PlayerStateMachine::run(entt::registry &registry, float delta_time) {
    auto view = registry.view<Velocity, Transform, Character, Animator>();
    auto cameraView = registry.view<Camera>();
    auto& camera = cameraView.get<Camera>(World::camera);
    for (auto ent : view) {
        auto [velocity, transform, character, animator] = view.get(ent);
        switch (character.state) {
            case Character::State::IDLE:
            case Character::State::WALK: {
                player_flip(&transform);
                character.state = play_walk(&velocity, &transform, &animator, &camera, delta_time);
            }
            default: ;
        }
    }
}

void PlayerStateMachine::player_flip(Transform *tr) {
    if (Input::state[SDL_SCANCODE_RIGHT]) {
        tr->flip = SDL_FLIP_NONE;
    } else if (Input::state[SDL_SCANCODE_LEFT]) {
        tr->flip = SDL_FLIP_HORIZONTAL;
    }
}

int PlayerStateMachine::play_walk(Velocity *vc, Transform *tr, Animator *am, const Camera* camera, const float delta_time) {
    auto state = Character::State::WALK;

    bool running = false;

    auto map = World::current_map;

    float x = (tr->position.x - camera->viewport.x) * camera->zoom + camera->viewport.w / 2 - tr->width / 2;
    float y = (tr->position.y - camera->viewport.y) * camera->zoom + camera->viewport.h / 2 - tr->height / 2;

    if (Input::state[SDL_SCANCODE_RIGHT]) {
        if (map->is_walkable(x, y + tr->height)) {
            vc->x = vc->max_speed * delta_time;
            tr->flip = SDL_FLIP_NONE;
            running = true;
            tr->position.x += vc->x;
            am->play("run");
        } else {
            tr->position.x -= 20;
        }
    }
    if (Input::state[SDL_SCANCODE_LEFT]) {
        if (map->is_walkable(x, y + tr->height)) {
            vc->x = -vc->max_speed * delta_time;
            tr->flip = SDL_FLIP_HORIZONTAL;
            running = true;
            tr->position.x += vc->x;
            am->play("run");
        } else {
            tr->position.x += 20;
        }
    }
    if (Input::state[SDL_SCANCODE_DOWN]) {
        if (map->is_walkable(x, y + tr->height)) {
            vc->y = vc->max_speed * delta_time;
            running = true;
            tr->position.y += vc->y;
            am->play("run");
        } else {
            tr->position.y -= 20;
        }

    }
    if (Input::state[SDL_SCANCODE_UP]) {
        if (map->is_walkable(x, y + tr->height)) {
            vc->y = -vc->max_speed * delta_time;
            tr->flip = SDL_FLIP_HORIZONTAL;
            running = true;
            tr->position.y += vc->y;
            am->play("run");
        } else {
            tr->position.y += 20;
        }
    }

    if (!running) {
        if (tr->flip == SDL_FLIP_NONE) {
            am->current_anim = "idle";
        } else {
            tr->flip = SDL_FLIP_NONE;
        }
    }
    return 0;
}
