#pragma once

#include "Animation.hpp"
#include "Collision.hpp"

class Princess : public GameObject
{
public:
    Princess(const std::pair<int, int> pos, const bool& faceRightStart);
    ~Princess();

    Collision* getCollision() { return collision; }
    void render();
    void update(const Uint32& deltaTime);

    bool faceRight = false;
private:
    Collision* collision = nullptr;
    Animation* animation = nullptr;

    bool faceRightStart;
};
