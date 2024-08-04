#include "Game.hpp"
#include "GameWindow.hpp"

#include <iostream>
#include <SDL_image.h>

GameWindow* gWin = new GameWindow();
SDL_Window* window;
SDL_Renderer* renderer;

enum Menu{
	PLAYGAME,
	INSTRUCTION,
	EXIT,
	MENU
};

void start() {
    if(gWin->init()) {
        gWin->setUp();
    }


}
