#include "Game.hpp"

#include <iostream>
#include <SDL_image.h>

bool init()
{
    bool isRunning = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Set texture filtering to linear
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //create window
    gWindow = SDL_CreateWindow("Run Run Run", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cout << "Window could not be created! SDL Error:" << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else
    {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL)
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 88, 128, 204, 255);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << std::endl;
                isRunning = false;
            }
        }
    }
    return isRunning;
}

void start() {

}
