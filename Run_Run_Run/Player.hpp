#pragma once

#include <cmath>
#include <functional>
#include <utility>
#include <string>

#include "Collision.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player(std::pair<int, int> pos, const bool& face);
    ~Player();

    void render();
    Collision* getCollision() { return collision; }

    void update(const Uint32& deltaTime);
    void applyGravity(const Uint32& deltaTime);
    void resetState();
    bool shouldMovePlayer() const;
    void movePlayer(const Uint32& deltaTime);
    void jump();
    void handleInput(const Uint32& deltaTime);

    void updateAnimation(const Uint32& deltaTime);
    bool updateStart(const Uint32& deltaTime);
    bool updateEnd(const Uint32& deltaTime);
    void updateMove(const Uint32& deltaTime);
    void reset();

    bool faceRight = false;
    float jumHeight = 180.0f;
    std::pair<int, int> vel = {0, 0};
    bool start = true;
    bool end = false;
    bool deletePlayer = false;
    bool canJump = false;
    bool winGame = false;
private:
    GameObject player;
    Animation* animation;
    float speed = 100.0f;
    std::pair<int, int> posStart;
    std::pair<int, int> posOld;
    bool face_Right;

    Collision* collision = nullptr;

};
