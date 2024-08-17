#pragma once

#include "GameObject.hpp"
#include "Collision.hpp"
#include "Animation.hpp"

class Monster : public GameObject
{
public:
    Monster(int type, const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& pos);
    ~Monster();

    void update(const Uint32& deltaTime);
    void render();
    Collision* getCollision() { return collision; }

    int checkDeath;
    bool deleteBot;
    float speed;
    bool faceRight;
    int _move;
    int type;
private:
    Animation* animation = nullptr;
    Collision* collision = nullptr;
    std::pair<int, int> start, end;
    std::pair<int, int> frameCount;
};
