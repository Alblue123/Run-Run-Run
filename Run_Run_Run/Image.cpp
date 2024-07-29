#include "Image.hpp"

Image::Image(GameWindow) {
    scale = 1;
}

Image::~Image() {
}

void Image::loadTexture(const char* path) {
	this->tex = IMG_LoadTexture(this->mWin->renderer, path);
	int w, h;
	SDL_QueryTexture(mTex, NULL, NULL, &w, &h);
	this->rex.x = this->pos.x; rex.y = this->pos.y; rex.w = w; rex.h = h;
}

void Image::draw() {
	mWin->draw(this->mTex, NULL, &rex);
}

void Image::update() {
	texr.x = pos.x;
	texr.y = pos.y;
}

SDL_Rect Image::getRect() {
	return this->rex;
}

void Image::setHeight(int h) {
	rex.h = h;
}

void Image::setPosCenter(Vector2 pos) {
	this->pos.x = pos.x - rex.w/2;
	this->pos.y = pos.y - rex.h/2;
}

void Image::setPosCenter(int x, int y){
	this->pos.x = x - rex.w/2;
	this->pos.y = y - rex.h/2;
}

Vector2 Image::getPos() {
    return pos;
}
