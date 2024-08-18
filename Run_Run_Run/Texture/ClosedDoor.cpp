#include "ClosedDoor.hpp"

ClosedDoor::ClosedDoor(const std::pair<int, int>& pos)
    : open(false) {
    animation = new Animation("Data//Textures/ClosedDoor//strange_door.png", {11, 2}, 75);
    loadIMG("Data//Textures/ClosedDoor//strange_door.png");
    setSize({40, 100});
    setRect(pos);
    collision = new Collision(*this);
}

ClosedDoor::~ClosedDoor() {
    delete collision;
    delete animation;
}

void ClosedDoor::update(const Uint32& deltaTime) {
    animation->currTime += deltaTime;

    if (animation->currTime >= animation->getSwitchTime()) {
        animation->currTime -= animation->getSwitchTime();

        if (open) {
            if (animation->currFrame.second == 1) {
                if (animation->currFrame.first < animation->getFrameCount().first)
                    animation->currFrame.first++;
            } else {
                animation->currFrame = {0, 1};
            }
        } else {
            if (animation->currFrame.second == 1) {
                if (animation->currFrame.first > 0)
                    animation->currFrame.first--;
                else
                    animation->currFrame.second = 0;
            } else {
                animation->currFrame.first++;
                if (animation->currFrame.first >= 10)
                    animation->currFrame.first = 0;
            }
        }
    }

    animation->update(false);
}

void ClosedDoor::render() {
    GameObject::render(0, animation->getRect());
}

