#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include <vector>

class Instruction
{
public:
    Instruction() {}
    ~Instruction();

    void init();
    void render();

private:
    GameObject* bg;
    GameObject* title;
    GameObject* main;
    GameObject* nextState;
};
