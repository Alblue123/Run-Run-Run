#include "Treasure.hpp"

Treasure::Treasure(const std::pair<int, int>& pos)
    : animation(new Animation("Data//Textures//Treasure//treasure.png", {1, 1}, 100)),
      collision(new Collision(*this)),
      item(0) {

    setSize({32, 32});
    loadIMG("Data//Textures//Treasure//treasure.png");
    setRect(pos);
    animation->currFrame = {0, 0};
}

Treasure::~Treasure() {
    delete animation;
    delete collision;
}

void Treasure::update(const Uint32& deltaTime) {
    if (item == 0) {
        animation->update(deltaTime, {1, 0});
    } else if (item == 1) {
        item++;
        loadIMG("Data//Textures//Treasure//treasure_open.png");
    }
}

void Treasure::render() {
    if (item != 0) {
        GameObject::render();
    } else {
        GameObject::render(0, animation->getRect());
    }
}
