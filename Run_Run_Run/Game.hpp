#pragma once

#include <SDL.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;

//Screen
const int FPS = 30;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;
const int gPixelBit = 32;

void start();
