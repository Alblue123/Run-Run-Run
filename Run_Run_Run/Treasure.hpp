#pragma once

#include "Animation.hpp"
#include "Collision.hpp"

class Treasure : public GameObject
{
public:
    Treasure(const std::pair<int, int>& pos);
    ~Treasure();

    void render();
    void update(const Uint32& deltaTime);

    Collision* getCollision() {return collision; }

    int item = 0;
private:
    Animation* animation = nullptr;
    Collision* collision = nullptr;
};
