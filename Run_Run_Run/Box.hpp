#pragma once

#include "Animation.hpp"
#include "Collision.hpp"
#include "GameObject.hpp"

class Box : public GameObject
{
public:
     Box(const std::pair<int, int>& pos);
    ~Box();

    void render();
    void update(const Uint32& deltaTime);
    Collision* getCollision() { return collision; }
    void limitPos();

    bool canDrop;
    GameObject player;
private:
    std::pair<float, float> vel;
    Collision* collision = nullptr;
};
