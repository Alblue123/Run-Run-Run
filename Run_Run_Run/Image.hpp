#pragma once

#include <SDL.h>
#include "GameWindow.hpp"

class Image
{
public:
    Image(GameWindow* mWin);
    ~Image();

    SDL_Rect getRect();
    void setPosCenter(Vector2 pos);
    void setPosCenter(int x, int y);
    void setHeight(int h);
    void draw();
    void loadTexture(const char* path);
    void update();
    Vector2 getPos();
    float scale;

private:
    Vector2 pos;
    GameWindow* mWin;
    SDL_Rect rex;
    SDL_Texture* mTex;

};
