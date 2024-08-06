#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "Timer.hpp"

//Screen
const int FPS = 60;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;
const int gPixelBit = 32;
//color

const int COLOR_KEY_R = 171;
const int COLOR_KEY_G = 173;
const int COLOR_KEY_B = 171;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

const int frameDelay = 1000 / FPS;
extern Uint32 frameStart;
extern unsigned int frameTime;

void start();
