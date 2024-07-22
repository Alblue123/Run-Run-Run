#pragma once

#include <SDL.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


//Screen
const int FPS = 30;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;
const int gPixelBit = 32;

//color

const int COLOR_KEY_R = 171;
const int COLOR_KEY_G = 173;
const int COLOR_KEY_B = 171;

void start();
