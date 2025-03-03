//
// Created by seirar on 3/2/2025.
//
module;

#include <vector>

export module Character;

export struct Character {
    struct State {
        static constexpr int IDLE = 0;
        static constexpr int WALK = 1;
        static constexpr int JUMP = 2;
        static constexpr int DIE = 3;
    };
    int state = State::IDLE;
};