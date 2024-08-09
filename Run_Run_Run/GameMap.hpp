#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "GameObject.hpp"
#include "Surface.hpp"
#include "Player.hpp"

class GameMap
{
public:
    GameMap();
    ~GameMap();

    void loadMap(std::string path);
    void render();
    void renderBackground();
    void renderSurface();
    void renderPlayer();

    void update(const Uint32& deltaTime);

    void updatePlayer(const Uint32& deltaTime);

    void setCollisionSurfacePlayer(Surface** surface, Player* player, int& width, int& height);

    Player* getPlayer() { return player; }

    bool win;
    int exit = 0;

private:
    int width, height;
    GameObject* background;
    Surface** surface;

    Player* player;
};
