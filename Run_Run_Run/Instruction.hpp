#include "Game.hpp"
#include "GameObject.hpp"

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
