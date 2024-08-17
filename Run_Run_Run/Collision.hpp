#pragma once

#include "GameObject.hpp"
#include <cmath>
#include <algorithm>

enum collision {
     top = 8, right = 6, left = 4, down = 2,
    _top = -8, _right = -6, _left = -4, _down = -2,
};

class Collision
{
public:
    Collision(GameObject* object);
    Collision(GameObject& object);
    ~Collision();

    int checkCollision(Collision* other, float push);
    int checkCollision(Collision* other);
    std::pair<float, float> getCenterPos();
    std::pair<int, int> getPos();
    std::pair<int, int> getSize();
    void moveObject(std::pair<int, int> pos);

    GameObject* object;
};
