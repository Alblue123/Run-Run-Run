#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.hpp"
#include "GameObject.hpp"
#include "GameMap.hpp"

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    void handleEvents();
    void render();
    void free();
    bool init();
    void update(const Uint32& deltaTime);
    void setUp();
    bool getRunning();

    int curMap = 1;
private:
    bool checkRunning;
    GameMap* mainMap;
    GameObject* background;
    bool WIN = false;
    bool LOOSE = false;


};
