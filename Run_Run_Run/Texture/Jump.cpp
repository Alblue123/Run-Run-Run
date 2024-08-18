#include "Jump.hpp"


Jump::Jump(const std::pair<int, int>& pos)
{
  animation = new Animation("Data//Textures//Jump//jump.png", {6, 1}, 100);
  loadIMG("Data//Textures//Jump//jump.png");
  setSize({32, 32});
  setRect(pos);

  collision = new Collision(*this);

}

Jump::~Jump()
{
    if (collision != nullptr){
        delete collision;
    }
    if (animation != nullptr){
        delete animation;
    }
}

void Jump::update(const Uint32& deltaTime){
    animation->update(deltaTime, {6, 0}, false);
}

void Jump::render(){
    GameObject::render(false, animation->getRect());
}
