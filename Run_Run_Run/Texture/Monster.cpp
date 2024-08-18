#include "Monster.hpp"

Monster::Monster(int type, const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& pos) {
    collision = new Collision(*this);
    this->type = type;
    _move = 0;
    faceRight = false;
    deleteBot = false;
    checkDeath = 0;
    speed = 16;

    if (type == 1) {
        animation = new Animation("Data//Textures//Monster//skull_wolf.png", {7, 4}, 300);
        loadIMG("Data//Textures//Monster//skull_wolf.png");
        setSize({50, 50});
        setRect(pos);
        frameCount = {7, 1};

    } else if (type == 2) {
        animation = new Animation("Data//Textures//Monster//slime.png", {8, 3}, 150);
        loadIMG("Data//Textures//Monster//slime.png");
        setSize({50, 50});
        setRect(pos);
        frameCount = {8, 1};
    } else if (type == 3) {
        animation = new Animation("Data//Textures//Monster//mushroom.png", {8, 4}, 150);
        loadIMG("Data//Textures//Monster//mushroom.png");
        setSize({50, 50});
        setRect(pos);
        frameCount = {8, 0};
    }

    this->start = start;
    this->end = end;
    if (start.first < end.first) {
        _move = 1;
    } else {
        _move = -1;
        std::swap(this->start, this->end);
    }
}

Monster::~Monster() {
    if (collision != nullptr) {
        delete collision;
    }
    if (animation != nullptr) {
        delete animation;
    }
}

void Monster::update(const Uint32& deltaTime) {
    if (deleteBot) {
        return;
    }

    if (checkDeath == 1) {
        checkDeath++;
        if (type == 1) {
            frameCount = {6, 3};
            animation->currFrame = {0, 3};
        } else if (type == 2) {
            frameCount = {4, 2};
            animation->currFrame = {0, 2};
        } else if (type == 3) {
            frameCount = {5, 2};
            animation->currFrame = {0, 2};
        }
    }

    if (_move == 1) {
        faceRight = (type == 2);
    } else {
        faceRight = (type != 2);
    }

    if (_move == 1) {
        if (getPos().first > end.first) {
            setRect({end.first, getPos().second});
            _move = -1;
        }
    } else {
        if (getPos().first < start.first) {
            setRect({start.first, getPos().second});
            _move = 1;
        }
    }

    if (animation->update(deltaTime, frameCount, faceRight) && checkDeath) {
        deleteBot = true;
    }

    movePos({static_cast<float>(_move) * speed * deltaTime * 0.01f, 0});
}

void Monster::render() {
    GameObject::render(faceRight, animation->getRect());
}
