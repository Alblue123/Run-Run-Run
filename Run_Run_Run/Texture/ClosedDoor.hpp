#pragma once

#include "GameObject.hpp"
#include "Collision.hpp"
#include "Animation.hpp"

class ClosedDoor : public GameObject
{
public:
    ClosedDoor(const std::pair<int, int>& pos);
    ~ClosedDoor();
    void update(const Uint32& deltaTime);
    void render();
    Collision* getCollision() {return collision; }
    bool checkOpen(){ return open; }
    void setOpen(const bool& openDoor) { open = openDoor; }
private:
    Animation* animation = nullptr;
    Collision* collision = nullptr;
    bool open;
};
