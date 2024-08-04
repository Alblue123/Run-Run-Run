#include "Game.hpp"
#include "GameWindow.hpp"

#include <iostream>
#include <SDL_image.h>

GameWindow* gWin = new GameWindow();

enum Menu{
	PLAYGAME,
	INSTRUCTION,
	EXIT,
	MENU
};

void start() {
    gWin->init();
    int type = PLAYGAME;



}
