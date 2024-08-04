#pragma once

#include "GameObject.hpp"

enum collision {
    TOP,
    RIGHT,
    LEFT
    DOWN,
};

class Collision
{
public:
    Collision(GameObject* object);
    ~Collision();

    int checkCollision(GameObject* other);
    std::pair<float, float> getCenterPos();
    std::pair<int, int> getPos();
    std::pair<int, int> getSize();
    void moveObject(std::pair<int> pos);

    GameObject* object;


};
