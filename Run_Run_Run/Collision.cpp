#include "Collision.hpp"

Collision::Collision(GameObject* object) {
    this->object = object;
}

Collision::~Collision() {}

int Collision::checkCollision(Collision* other) {
    std::pair<float, float> otherCenterPos = other->getCenterPos();
    std::pair<int, int> otherSize = other->getSize();
    std::pair<float, float> currentCenterPos = getCenterPos();
    std::pair<int, int> thisSize = getSize();

    float deltaX = otherCenterPos.first - currentCenterPos.first;
    float deltaY = otherCenterPos.second - currentCenterPos.second;

    int intersectX = 2 * abs(deltaX) - (otherSize.first + thisSize.first);
    int intersectY = 2 * abs(deltaY) - (otherSize.second + thisSize.second);

    if (intersectX < 0 && intersectY < 0) {
        if (intersectX > intersectY) {
            return deltaX > 0.0f ? collision::right : collision::left;
        } else {
            return deltaY > 0.0f ? collision::down : collision::top;
        }
    } else if (intersectX <= 0 && intersectY <= 0) {
        if (intersectX > intersectY) {
            return deltaX > 0.0f ? collision::_right : collision::_left;
        } else {
            return deltaY > 0.0f ? collision::_down : collision::_top;
        }
    }

    return 0;
}


std::pair<float, float> Collision::getCenterPos() {
    return {(float) object->getPos().first + object->getSize().first/2,
     (float) object->getPos().second + object->getSize().second/2};
}

std::pair<int, int> Collision::getPos(){
    return object->getPos();
}
std::pair<int, int> Collision::getSize() {
    return object->getSize();
}

void Collision::moveObject(std::pair<int, int> pos) {
    object->movePos(pos);
}
