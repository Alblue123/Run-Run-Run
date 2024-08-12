#include "Spikes.hpp"
#include <iostream>

Spikes::Spikes(const std::pair<int, int> pos, bool dir)
    : dir(dir),
      animation(new Animation("Data//Textures//Spikes//spikes" + std::to_string(dir) + ".png", {2, 1}, 0)),
      collision(new Collision(*this)) {
    setSize({32, 100});
    setRect(pos);
    loadIMG("Data//Textures//Spikes//spikes" + std::to_string(dir) + ".png");
}

Spikes::~Spikes() {
    delete animation;
    delete collision;
}

bool Spikes::checkPlayer(Player* player) {
    if (!player) return false;
    return (dir ? checkUp(player) : checkDown(player));
}

bool Spikes::checkUp(Player* player) {
    int collisionResult = collision->checkCollision(player->getCollision());
    return (collisionResult == collision::top || collisionResult == collision::_top);
}

bool Spikes::checkDown(Player* player) {
    if (!player || player->end) return false;

    if (touchGround) {
        int collisionResult = collision->checkCollision(player->getCollision(), 1.0f);
        if (collisionResult == collision::top || collisionResult == collision::_top) {
            player->canJump = true;
        }
        return false;
    }

    if (!canDrop && std::abs(getPos().first - player->getPos().first) <= 10 &&
        (0 <= player->getPos().second - getPos().second &&
         player->getPos().second - getPos().second <= 200)) {
        canDrop = true;
        animation->currFrame.first = 1;
    }

    int collisionResult = collision->checkCollision(player->getCollision());
    return (collisionResult == collision::down || collisionResult == collision::_down);
}

void Spikes::update(const Uint32& deltaTime) {
    if (dir == 0 && canDrop && !touchGround) {
        vel.second += static_cast<float>(deltaTime) / 50;
        movePos(vel);
    }
    animation->update();
}

void Spikes::render() {
    GameObject::render(0, animation->getRect());
}
