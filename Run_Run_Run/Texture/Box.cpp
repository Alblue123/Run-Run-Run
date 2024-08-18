#include "Box.hpp"

Box::Box(const std::pair<int, int>& pos) {
    object.loadIMG("Data//Textures//Box//box.png");
    object.setSize({36, 36});
    object.setRect(pos);
    collision = new Collision(object);
    canDrop = true;
}

Box::~Box() {
    delete collision;
}

void Box::render() {
    object.render(false);
}

void Box::update(const Uint32& deltaTime) {
    if (canDrop) {
        vel.second += 0.01f * (float)deltaTime;
    } else {
        vel.second = 0;
    }
    object.movePos(vel);
    canDrop = true;
    limitPos();
}

void Box::limitPos() {
    if (object.getPos().first < 0) {
        object.setRect({0,object.getPos().second});
    }
    if (object.getPos().first + object.getSize().first > SCREEN_WIDTH) {
        object.setRect({SCREEN_WIDTH - object.getSize().first, object.getPos().second});
    }
}
