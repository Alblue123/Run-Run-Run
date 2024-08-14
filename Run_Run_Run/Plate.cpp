#include "Plate.hpp"

Plate::Plate(const std::pair<int, int>& pos)
    : stepped(false) {
    animation = new Animation("Data//Textures//Plate//buttom_pressed.png", {2, 1}, 100);
    loadIMG("Data//Textures//Plate//buttom_pressed.png");
    setSize({30, 6});
    setRect(pos);
    collision = new Collision(*this);
}

Plate::~Plate() {
    delete collision;
    delete animation;
}

void Plate::update() {
    animation->currFrame.first = stepped ? 1 : 0;
    animation->update(false);
}

void Plate::render() {
    GameObject::render(0, animation->getRect());
}

int Plate::checkCollision(Collision* other, const Uint32& deltaTime) {
    int collisionResult = collision->checkCollision(other, 1.0f);

    if (collisionResult != 0) {
        stepped = true;
    }

    if (collisionResult == collision::_left || collisionResult == collision::_right) {
        float moveAmount = static_cast<float>(deltaTime) / 10.0f;
        other->moveObject({moveAmount, 0.0f});
        other->object->setRect({other->getPos().first, getPos().second - other->getSize().second});
    }

    return collisionResult;
}
