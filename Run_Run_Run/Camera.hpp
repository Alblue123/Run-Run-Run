#pragma once

#include "Vector2.hpp"
#include "Game.hpp"
#include <SDL.h>
#include <algorithm>

class Camera
{
public:
   Vector2 portOffset;
   void setViewPortOffset(Vector2 Offpos);
   void centerOn(Vector2 pos);
   void follow(Vector2 pos);
   Vector2 getCenter();
};
