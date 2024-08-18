#pragma once

#include "Animation.hpp"
#include "Collision.hpp"
#include "GameObject.hpp"
#include "Player.hpp"

class Spikes : public GameObject
{
 public:
    Spikes(const std::pair<int, int> pos, bool dir);
    ~Spikes();

    void update(const Uint32& deltaTime);
    Collision* getCollision(){ return collision; }
    bool checkPlayer(Player* player);
    void render();
    std::pair<float, float> vel = {0.0f, 0.0f};
    bool canDrop = false;
    bool touchGround = false;

    bool checkUp(Player* player);
    bool checkDown(Player* player);
private:
    bool dir;
    Animation* animation = nullptr;
    Collision* collision = nullptr;
};
