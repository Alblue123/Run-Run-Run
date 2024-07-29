#include "Game.hpp"
#include "GameWindow.hpp"

#include <iostream>
#include <SDL_image.h>

GameWindow* gWin = new GameWindow();
Timer frameTime;

enum Menu{
	PLAYGAME,
	INSTRUCTION,
	EXIT,
	MENU
};

void start() {
    gWin->init();



}
