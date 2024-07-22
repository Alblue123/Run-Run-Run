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
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;

    GameWindow();
    ~GameWindow();

    //setter getter
    void setRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
    SDL_Rect getRect() const { return rect; }
    SDL_Texture* GetObject() const { return mTexture; }

    virtual bool loadIMG(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* renderer, const SDL_Rect* clip = NULL);
    void free();
    bool init();


protected:
    SDL_Texture* mTexture;
    SDL_Rect rect;
};
