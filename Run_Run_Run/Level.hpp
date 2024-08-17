#pragma once

#include <vector>

#include "Collision.hpp"
#include "Animation.hpp"

class Level {
public:
    Level(const std::pair<int, int>& pos);
    ~Level();

    void addWall(const std::pair<int, int>& pos, int type);
    void update(const Uint32& deltaTime);
    void render();
    bool shouldRestartStatus();

    GameObject _switch;
    Collision* colliderSwitch;
    bool isOpen;
    int statusDuration;
    std::vector<std::pair<std::pair<GameObject*, Collision*>, int>> _wallSegments;
};
