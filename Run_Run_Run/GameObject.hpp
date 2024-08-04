#pragma once

#include "Game.hpp"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void setRect(std::pair<int, int> pos) { rect.x = pos.first, rect.y = pos.second; }
    void setSize(std::pair<int, int> size) { rect.w = size.first, rect.h = size.second; }
    void movePos(std::pair<int, int> pos);
    SDL_Rect getRect() const { return rect; }
    SDL_Texture* GetObject() const { return mTexture; }
    std::pair<int, int> getPos() const { return {rect.x, rect.y}; }
	std::pair<int, int> getSize() const { return {rect.w, rect.h}; }

    virtual bool loadIMG(std::string path);
    void render(bool flip = 0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL);
    void free();


protected:
    SDL_Texture* mTexture;
    SDL_Rect rect;
};
