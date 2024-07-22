#include "Game.hpp"
#include "GameWindow.hpp"

#include <iostream>
#include <SDL_image.h>

GameWindow* gWin = new GameWindow();

void start() {
    gWin->init();
}
