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

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    void handleEvents();
    void render();
    void free();
    bool init();
    void setUp();
    bool getRunning();


private:
    bool checkRunning;
    GameObject* background;

};
