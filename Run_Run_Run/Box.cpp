#include "Box.hpp"

Box::Box(const std::pair<int, int>& pos) {
    player.loadIMG("Data//Textures//Box//box.png");
    player.setSize({36, 36});
    player.setRect(pos);
    collision = new Collision(player);
    canDrop = true;
}

Box::~Box() {
    delete collision;
}

void Box::render() {
    player.render(false);
}

void Box::update(const Uint32& deltaTime) {
    if (canDrop) {
        vel.second += 0.01f * (float)deltaTime;
    } else {
        vel.second = 0;
    }
    player.movePos(vel);
    canDrop = true;
    limitPos();
}

void Box::limitPos() {
    if (player.getPos().first < 0) {
        player.setRect({0, player.getPos().second});
    }
    if (player.getPos().first + player.getSize().first > SCREEN_WIDTH) {
        player.setRect({SCREEN_WIDTH - player.getSize().first, player.getPos().second});
    }
}
