#pragma once

#include "Animation.hpp"
#include "Collision.hpp"
#include "GameObject.hpp"

class Cherry : public GameObject
{
public:
    Cherry(std::pair<int, int> pos);
    ~Cherry();

    void update(const Uint32& deltaTime);
    void render();
    Collision* getCollision() { return collision; }

    bool delCherry;
    int eatCherry;
private:
    Animation* animation = nullptr;
    Collision* collision = nullptr;
};
