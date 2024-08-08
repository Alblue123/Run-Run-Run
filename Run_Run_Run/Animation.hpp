#pragma once

#include <SDL.h>

#include "Game.hpp"

class Animation
{
public:
    Animation(const std::string& name, std::pair<int, int> frameCount, Uint32 switchTime);
    ~Animation();

    bool update(Uint32 deltaTime, std::pair<int, int> frameLimit, bool faceRight);
    bool update(Uint32 deltaTime, bool faceRight);
    bool update(Uint32 deltaTime, std::pair<int, int> frameLimit);
    bool update(Uint32 deltaTime);
    void update(bool faceRight);
    void update();

    Uint32 getSwitchTime() const { return switchTime; }
    void setSwitchTime(Uint32 switchTime);

    std::pair<int, int> getFrameCount() const { return frameCount; }
    SDL_Rect* getRect() { return &box; }
    bool getFlip() const { return flip; }

private:
    std::pair<int, int> frameCount;
    Uint32 switchTime;
    SDL_Surface* surface;
    SDL_Rect box;
    bool flip;

    std::pair<int, int> currFrame;
    Uint32 currTime;
};
