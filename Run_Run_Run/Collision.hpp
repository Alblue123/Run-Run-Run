#pragma once

#include "GameObject.hpp"

enum collision {
     top = 1, right = 2, left = 3, down = 4,
    _top = -1, _right = -2, _left = -3, _down = -4,
};

class Collision
{
public:
    Collision(GameObject* object);
    Collision(GameObject& object);
    ~Collision();

    int checkCollision(Collision* other);
    std::pair<float, float> getCenterPos();
    std::pair<int, int> getPos();
    std::pair<int, int> getSize();
    void moveObject(std::pair<int, int> pos);

    GameObject* object;
};
