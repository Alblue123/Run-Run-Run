#pragma once

#include "Animation.hpp"
#include "Collision.hpp"

class Jump : public GameObject
{
public:
    Jump(const std::pair<int, int>& pos);
    ~Jump();

    void render();
    void update(const Uint32& deltaTime);

    Collision* getCollision() { return collision; }
private:
    Animation* animation = nullptr;
    Collision* collision = nullptr;
};
