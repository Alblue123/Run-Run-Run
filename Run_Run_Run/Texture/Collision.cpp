#include "Collision.hpp"

Collision::Collision(GameObject* object) {
    this->object = object;
}

Collision::Collision(GameObject& object) {
    this->object = &object;
}

Collision::~Collision() {}

int Collision::checkCollision(Collision* other,float push) {
    std::pair<int, int> otherPosition = other->getPos();
    std::pair<float, float> otherCenterPosition = other->getCenterPos();
    std::pair<int, int> otherSize = other->getSize();
    std::pair<int, int> thisPosition = getPos();
    std::pair<float, float> thisCenterPosition = getCenterPos();
    std::pair<int, int> thisSize = getSize();
    float deltaX = 2 * otherPosition.first + otherSize.first - 2 * thisPosition.first - thisSize.first;
    float deltaY = 2 * otherPosition.second + otherSize.second - 2 * thisPosition.second - thisSize.second;
    float intersectX = abs(deltaX) - (otherSize.first + thisSize.first);
    float intersectY = abs(deltaY) - (otherSize.second + thisSize.second);
    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                if (push == 1.0f) {
                    other->object->setRect({thisPosition.first + thisSize.first, other->object->getPos().second});
                    return collision::_right;
                }
                int curMove = intersectX * (1.0f - push);
                moveObject({curMove, 0.0f});
                other->moveObject({- intersectX + curMove, 0.0f});
                return collision::right;
            }
            else {
                if (push == 1.0f) {
                    other->object->setRect({thisPosition.first - otherSize.first, other->object->getPos().second});
                    return collision::_left;
                }
                int curMove = intersectX * (1.0f - push);
                moveObject({-curMove, 0.0f});
                other->moveObject({intersectX - curMove, 0.0f});
                return collision::left;
            }
        }
        else {
            if (deltaY > 0.0f) {
                if (push == 1.0f) {
                    other->object->setRect({other->object->getPos().first, thisPosition.second + thisSize.second});
                    return collision:: _down;
                }
                int curMove = intersectY * (1.0f - push);
                moveObject({0.0f, curMove});
                other->moveObject({0.0f, - intersectY + curMove});
                return collision::down;
            }
            else {
                if (push == 1.0f) {
                    other->object->setRect({other->object->getPos().first, thisPosition.second - otherSize.second});
                    return collision::_top;
                }
                int curMove = intersectY * (1.0f - push);
                moveObject({0.0f, - curMove});
                other->moveObject({0.0f, intersectY - curMove});
                return collision::top;
            }
        }
    }
    if (intersectX <= 0.0f && intersectY <= 0.0f) {
        if (intersectX == 0.0f && intersectY < 0.0f) {
            if (thisCenterPosition.first < otherCenterPosition.first) {
                return collision::_right;
            }
            else {
                return collision::_left;
            }
        }
        if (intersectY == 0.0f && intersectX < 0.0f) {
            if (otherCenterPosition.second < thisCenterPosition.second)
                return collision::_top;
        }
    }
    return 0;
}


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
