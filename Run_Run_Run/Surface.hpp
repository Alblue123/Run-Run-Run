#pragma once

#include <string>

#include "GameObject.hpp"
#include "Collision.hpp"

class Surface: public GameObject
{
public:
    Surface();
    ~Surface();

    void setSurface(const std::string& path, const std::pair<int, int>& pos, const int& surfaceType);
    Collision* getCollision() const { return collision; }
private:
    Collision* collision = nullptr;
};
