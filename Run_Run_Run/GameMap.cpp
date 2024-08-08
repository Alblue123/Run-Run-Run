#include "GameMap.hpp"

GameMap::GameMap() {
    width = 16;
    height = 32;
    surface = new Surface * [width];
    for (int i = 0; i < width; ++i) {
        surface[i] = new Surface[height];
    }

}

GameMap::~GameMap() {
    width = 0, height = 0;

    if (background != nullptr) {
        delete background;
    }
}

void GameMap::loadMap(std::string path) {
    background = new GameObject();
    background->loadIMG("Data/Textures/Background/Background1.png");
    background->setRect({0, 0});
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});

    std::ifstream map_file(path.c_str);
    if (map_file.fail()) {
        std::cout << "Error: Can't open map file!" << endl;
        return;
    }
}

void GameMap::render() {
    renderBackground();
    renderSurface();
}

void GameMap::renderBackground() {
    background->render(false);
}
void GameMap::renderSurface() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            surface[i][j].render();
        }
    }
}
