#include "Collision.hpp"

Collision::Collision(GameObject* object) {
    this->object = object;
}

Collision::Collision(GameObject& object) {
    this->object = &object;
}

Collision::~Collision() {}

int Collision::checkCollision(Collision* other, float push) {
    auto [otherPosX, otherPosY] = other->getPos();
    auto [otherCenterX, otherCenterY] = other->getCenterPos();
    auto [otherWidth, otherHeight] = other->getSize();

    auto [thisPosX, thisPosY] = getPos();
    auto [thisCenterX, thisCenterY] = getCenterPos();
    auto [thisWidth, thisHeight] = getSize();

    float deltaX = 2 * otherPosX + otherWidth - 2 * thisPosX - thisWidth;
    float deltaY = 2 * otherPosY + otherHeight - 2 * thisPosY - thisHeight;

    float intersectX = std::abs(deltaX) - (otherWidth + thisWidth);
    float intersectY = std::abs(deltaY) - (otherHeight + thisHeight);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::clamp(push, 0.0f, 1.0f);

        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                if (push == 1.0f) {
                    other->object->setRect({thisPosX + thisWidth, other->object->getPos().second});
                    return collision::_right;
                }
                float curMove = intersectX * (1.0f - push);
                moveObject({curMove, 0.0f});
                other->moveObject({-intersectX + curMove, 0.0f});
                return collision::right;
            } else {
                if (push == 1.0f) {
                    other->object->setRect({thisPosX - otherWidth, other->object->getPos().second});
                    return collision::_left;
                }
                float curMove = intersectX * (1.0f - push);
                moveObject({-curMove, 0.0f});
                other->moveObject({intersectX - curMove, 0.0f});
                return collision::left;
            }
        } else {
            if (deltaY > 0.0f) {
                if (push == 1.0f) {
                    other->object->setRect({other->object->getPos().first, thisPosY + thisHeight});
                    return collision::_down;
                }
                float curMove = intersectY * (1.0f - push);
                moveObject({0.0f, curMove});
                other->moveObject({0.0f, -intersectY + curMove});
                return collision::down;
            } else {
                if (push == 1.0f) {
                    other->object->setRect({other->object->getPos().first, thisPosY - otherHeight});
                    return collision::_top;
                }
                float curMove = intersectY * (1.0f - push);
                moveObject({0.0f, -curMove});
                other->moveObject({0.0f, intersectY - curMove});
                return collision::top;
            }
        }
    }

    if (intersectX <= 0.0f && intersectY <= 0.0f) {
        if (intersectX == 0.0f && intersectY < 0.0f) {
            return thisCenterX < otherCenterX ? collision::_right : collision::_left;
        }
        if (intersectY == 0.0f && intersectX < 0.0f) {
            return otherCenterY < thisCenterY ? collision::_top : collision::_down;
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
