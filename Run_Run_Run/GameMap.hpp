#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "GameObject.hpp"
#include "Surface.hpp"

class GameMap
{
public:
    GameMap();
    ~GameMap();

    void loadMap(std::string path);
    void render();
    void renderBackground();
    void renderSurface();

private:
    int width, height;
    GameObject* background;
    Surface** surface;
};
