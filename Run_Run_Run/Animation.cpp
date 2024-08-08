#include "Animation.hpp"

Animation::Animation(const std::string& name, std::pair<int, int> frameCount, Uint32 switchTime)
    : frameCount(frameCount), switchTime(switchTime), currFrame(0, 0), currTime(0), flip(false) {
    surface = IMG_Load(name.c_str());
    if (surface == NULL) {
        std::cout << "Cannot load image! SDL_image error: " << IMG_GetError() << std::endl;
    }
    box.w = surface->w / frameCount.first;
    box.h = surface->h / frameCount.second;
}

Animation::~Animation() {
    if (surface) {
        SDL_FreeSurface(surface);
    }
}

bool Animation::update(Uint32 deltaTime, std::pair<int, int> frameLimit, bool faceRight) {
    bool check = false;
    currTime += deltaTime;
    if (currTime >= switchTime) {
        currTime -= switchTime;
        if (currFrame.second != frameLimit.second) {
            currFrame = {0, frameLimit.second};
        } else {
            currFrame.first++;
            if (currFrame.first >= frameLimit.first) {
                currFrame.first = 0;
                check = true;
            }
        }
    }
    update(faceRight);
    return check;
}

bool Animation::update(Uint32 deltaTime, bool faceRight) {
    return update(deltaTime, {frameCount.first, 0}, faceRight);
}

bool Animation::update(Uint32 deltaTime, std::pair<int, int> frameLimit) {
    return update(deltaTime, frameLimit, flip);
}

bool Animation::update(Uint32 deltaTime) {
    return update(deltaTime, flip);
}

void Animation::update(bool faceRight) {
    box.y = currFrame.second * box.h;
    box.x = currFrame.first * box.w;
    flip = faceRight;
}

void Animation::update() {
    update(flip);
}

void Animation::setSwitchTime(Uint32 switchTime) {
    this->switchTime = switchTime;
}
