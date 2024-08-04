#include "GameMap.hpp"

GameMap::GameMap() {
    width = 12;
    height = 20;
}

GameMap::~GameMap() {
    width = 0, height = 0;

    if (background != nullptr) {
        delete background;
    }
}

void GameMap::loadMap(std::string path) {
    background = new GameObject();
    background->loadIMG("Resources/Textures/Background/Background1.png");
}
