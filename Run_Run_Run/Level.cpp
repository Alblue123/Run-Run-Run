#include "Level.hpp"

Level::Level(const std::pair<int, int>& pos)
    : _switch(), colliderSwitch(new Collision(_switch)), isOpen(false), statusDuration(0) {

    _switch.setSize({50, 50});
    _switch.setRect(pos);
}

Level::~Level() {
    delete colliderSwitch;

    for (auto& wall : _wallSegments) {
        delete wall.first.first;
        delete wall.first.second;
    }
}

void Level::addWall(const std::pair<int, int>& pos, int type) {
    _wallSegments.emplace_back(std::make_pair(new GameObject, nullptr), type);

    auto& wall = _wallSegments.back();

    wall.first.second = new Collision(wall.first.first);

    if (type == 1) {
        wall.first.first->setSize({100, 50});
    } else {
        wall.first.first->setSize({50, 100});
    }

    wall.first.first->setRect(pos);
}

void Level::update(const Uint32& deltaTime) {
    const std::string leverTexture = isOpen ?
        "Data//Textures//Level//lever_right.png" :
        "Data//Textures//Level//lever_left.png";
    _switch.loadIMG(leverTexture);

    if (statusDuration > 0) {
        statusDuration -= static_cast<int>(deltaTime);
    }

    const std::string wallTextureBase = "Data//Textures//Level//wood";
    const std::string wallTextureSuffix = isOpen ? "_open.png" : "_closed.png";

    for (auto& wall : _wallSegments) {
        const std::string wallTexture = wallTextureBase + wallTextureSuffix;
        wall.first.first->loadIMG(wallTexture);
    }
}

void Level::render() {
    _switch.render(false);

    for (auto& wall : _wallSegments) {
        wall.first.first->render(false);
    }
}

bool Level::shouldRestartStatus() {
    return statusDuration <= 0;
}

