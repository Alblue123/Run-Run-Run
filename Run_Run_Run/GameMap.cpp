#include "GameMap.hpp"

GameMap::GameMap() {
    width = 16;
    height = 32;
    player = nullptr;
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

    std::ifstream map_file(path.c_str());
    if (map_file.fail()) {
        std::cout << "Error: Can't open map file!" << std::endl;
        return;
    }
    std::string surface_path = "Data//Textures//Surface//";
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int surfaceType = 0;
            map_file >> surfaceType;
            if (!surfaceType) continue;
            std::string surfaces = surface_path + std::to_string(surfaceType);
            surfaces += ".png";
            surface[i][j].setSurface(surfaces, {j * gPixelBit, i * gPixelBit},  surfaceType);
        }
    }

    int x, y, type;
    map_file >> x >> y >> type;
    player = new Player({x, y}, type);

    map_file.close();
}

void GameMap::render() {
    renderBackground();
    renderSurface();
    renderPlayer();
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

void GameMap::renderPlayer() {
    if (player->deletePlayer == false) {
        player->render();
    }
}

void GameMap::update(const Uint32& deltaTime) {
    setCollisionSurfacePlayer(surface, player, width, height);

    updatePlayer(deltaTime);
}

void GameMap::updatePlayer(const Uint32& deltaTime) {
    if (player->deletePlayer) {
        exit = player->winGame ? 1 : 2;
        return;
    }

    player->update(deltaTime);
}

void GameMap::setCollisionSurfacePlayer(Surface** surface, Player* player, int& width, int& height) {
    if (!player) {
        return;
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto* collision = surface[i][j].getCollision();
            if (!collision) {
                continue;
            }

            int checkResult = collision->checkCollision(player->getCollision(), 1.0f);

            if (checkResult == collision::top || checkResult == collision::_top) {
                player->canJump = true;
            } else if (checkResult == collision::down || checkResult == collision::_down) {
                player->vel.second *= 0.8f;
            }
        }
    }
}
