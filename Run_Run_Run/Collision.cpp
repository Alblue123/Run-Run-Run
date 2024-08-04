#include "Collision.hpp"

Collision::Collision(GameObject* object) {
    this->object = object;
}

int Collision:checkCollision(GameObject* other) {

}

std::pair<float, float> Collision::getCenterPos() {
    return {(float) object->getPosition().first + object->getSize().first/2,
     (float) object->getPosition().second + object->getSize().second/2};
}

std::pair<int, int> Collision::getPos(){
    return object->getPosition();
}
std::pair<int, int> Collision::getSize() {
    return object->getSize();
}

void Collision::moveObject(std::pair<int, int> pos) {
    object->movePos(pos);
}
