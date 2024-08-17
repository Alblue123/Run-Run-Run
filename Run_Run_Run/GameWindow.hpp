#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include "Game.hpp"
#include "GameObject.hpp"
#include "GameMap.hpp"
#include "Instruction.hpp"
#include "Menu.hpp"

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    void handleEvents();
    void render();
    void renderGameOver();
    void renderWin();
    void renderPause();
    void free();
    bool init();
    void update(const Uint32& deltaTime);
    void setUp();

    bool getRunning() {return checkRunning; }
    bool isWinning() { return WIN; }
    bool isLosing() { return LOOSE; }

    int curMap = 1;
private:
    bool checkRunning;
    GameMap* mainMap;
    GameObject* background;
    bool WIN = false;
    bool LOOSE = false;
    GameObject* loose;
    GameObject* win;
    GameObject* gPause;
    GameObject* nextState;
    GameObject* unpause;
    GameObject* retry;

    GameObject* cherry1;
    GameObject* cherry2;
    GameObject* heart1;
    GameObject* heart2;

};
