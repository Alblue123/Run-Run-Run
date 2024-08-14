#pragma once

#include "Animation.hpp"
#include "Collision.hpp"
#include "GameObject.hpp"

class Plate : public GameObject
{
public:
    Plate(const std::pair<int, int>& pos);
    ~Plate();

    void update();
    void render();
    int checkCollision(Collision* other, const Uint32& deltaTime);
    Collision* getCollision() { return collision; }
    bool getStepped() { return stepped; }
    void setStepped(const bool& _stepped) { stepped = _stepped; }
private:
    Animation* animation = nullptr;
    Collision* collision = nullptr;
    bool stepped;
};
