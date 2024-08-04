#pragma once

#include <vector>
#include <string>

#include "GameObject.hpp"

class GameMap:
{
public:
    GameMap();
    ~GameMap();

    void loadMap(std::string path);
    void render();
    void renderBackground();

private:
    int width, height;
    GameObject* background;
};
