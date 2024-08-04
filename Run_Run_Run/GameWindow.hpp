#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.hpp"

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    void handleEvents();
    void render();
    void free();
    bool init();
    bool isRunning() {
        return isRunning;
    }


private:
    bool isRunning = false;

};
