#include "Cherry.hpp"

Cherry::Cherry(std::pair<int, int> pos)
    : delCherry(false), eatCherry(false)
{
    animation = new Animation("Data//Textures/Cherry//cherry.png", {9, 1}, 100);
    loadIMG("Data//Textures/Cherry//cherry.png");
    setSize({27, 27});
    setRect(pos);
    collision = new Collision(*this);
}

Cherry::~Cherry() {
    delete animation;
    delete collision;
}

void Cherry::update(const Uint32& deltaTime) {
    if (delCherry) return;

    if (eatCherry == 1) {
            animation = new Animation("Data//Textures/Cherry//cherry_eat.png", {4, 1}, 100);
            loadIMG("Data//Textures/Cherry//cherry_eat.png");
            setSize({27, 54});
            movePos({0, -27});
            eatCherry++;
            animation->currFrame.first = 0;
            animation->setSwitchTime(100);
    }

    if (animation->update(deltaTime) && eatCherry) {
        delCherry = true;
    }
}

void Cherry::render() {
    if (!delCherry) {
        GameObject::render(0, animation->getRect());
    }
}
