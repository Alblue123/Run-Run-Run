#include "Princess.hpp"

Princess::Princess(const std::pair<int, int> pos, const bool& faceRightStart){
    animation = new Animation("Data//Textures//Princess//Fairy1.png", {8, 1}, 130);
    loadIMG("Data//Textures//Princess//Fairy1.png");
    setSize({50, 50});
    setRect(pos);

    collision = new Collision(*this);
    faceRight = faceRightStart;

}

Princess::~Princess(){
    if (animation != nullptr) {
        delete animation;
    }

    if (collision != nullptr)
        delete collision;
}

void Princess::render(){
    GameObject::render(faceRight, animation->getRect());
}

void Princess::update(const Uint32& deltaTime) {
    animation->update(deltaTime, faceRight);
}
