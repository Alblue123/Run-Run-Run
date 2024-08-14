#pragma once

#include <cmath>
#include <functional>
#include <utility>
#include <list>
#include <string>
#include <SDL.h>

#include "Collision.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"

class Player: public GameObject {
public:
    Player(std::pair<int, int> pos, const bool& faceRightStart);
    ~Player();


    void update(const Uint32& deltaTime);
    void render();


    bool face_Right = false;
    float jumHeight = 100.0f;
    std::pair<int, int> vel = {0, 0};
    bool start = true;
    bool end = false;
    bool delPlayer = false;
    bool canJump = false;
    bool pushBox = false;
    bool wingame = false;

    Collision* getCollision() { return collision; }

    void updateAnimation(const Uint32& deltaTime);
    void applyGravity(const Uint32& deltaTime);
    void handleMovement(const Uint32& deltaTime);
    void updateShadow(const Uint32& deltaTime);
    bool updateStart(const Uint32& deltaTime);
    bool updateWinGame(const Uint32& deltaTime);
    bool updateAttack(const Uint32& deltaTime);
    bool updateEnd(const Uint32& deltaTime);
    bool updateTeleportation(const Uint32& deltaTime);
    bool updatePushBox(const Uint32& deltaTime);
    void updateMove(const Uint32& deltaTime);
    void limitPos();
    void reset();

private:
    GameObject player;
    Animation* animation;
    float speed = 160.0f;
    int timeClickS = 0;
    int teleportation = 0;
    std::pair<float, float> oldPos;
    std::pair<float, float> startPos;
    bool faceRightStart;
    Collision* collision = nullptr;

};
