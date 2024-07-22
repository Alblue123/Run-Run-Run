#pragma once

#include "Game.hpp"

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    //setter getter
    void setRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
    SDL_Rect getRect() const { return rect; }
    SDL_Texture* GetObject() const { return mTexture; }

    virtual bool loadIMG(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* renderer, const SDL_Rect* clip = NULL);
    void free();


protected:
    SDL_Texture* mTexture;
    SDL_Rect rect;
};
