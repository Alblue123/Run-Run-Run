#include "GameMap.hpp"

GameMap::GameMap() {
    win = false;
    width = 16;
    height = 32;
    player = nullptr;
    closedDoor = nullptr;
    princess = nullptr;
    level = nullptr;
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

    for (int i = 0; i < width; ++i) {
        delete[] surface[i];
    }

    if (player != nullptr) {
        delete player;
    }

    if (princess != nullptr) {
        delete princess;
    }
}

void GameMap::loadMap(std::string path) {
    background = new GameObject();
    background->loadIMG("Data//Textures//Background//Background1.png");
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

    int _totalCherry;
    map_file >> _totalCherry;
    for (int i = 0; i < _totalCherry; i++){
        int x, y;
        map_file >> x >> y;
        cherries.push_back(new Cherry({x - 13.5, y - 13.5}));
    }


    int x, y, type;
    map_file >> x >> y >> type;
    player = new Player({x, y}, type);

    int tolTrap = 0;
    map_file >> tolTrap; bool mtype;
    for (int i = 0; i < tolTrap; i++){
        map_file >> x >> y >> mtype;
        spikes.push_back(new Spikes({x, y}, mtype));
    }


    map_file >> x >> y;
    closedDoor = new ClosedDoor({x, y});


    int ptype;
    map_file >> x >> y >> ptype;
    princess = new Princess({x, y}, ptype);


    int tolPlate;
    map_file >> tolPlate;
    for (int i = 0; i < tolPlate; i++){
        map_file >> x >> y;
        plates.push_back(new Plate({x, y}));
    }

    int tolBox;
    map_file >> tolBox;
    for (int i = 0; i < tolBox; i++){
        map_file >> x >> y;
        boxes.push_back(new Box({x, y}));
    }

    int tolChest;
    map_file >> tolChest;
    for (int i = 0; i < tolChest; i++){
        map_file >> x >> y;
        treasures.push_back(new Treasure({x, y}));
    }

    int tolMon;
    std::pair<int, int> _pos, _start, _end;
    map_file >> tolMon;
    for (int i = 0; i < tolMon; i++){
        map_file >> type >> _pos.first >> _pos.second >> _start.first >> _start.second >> _end.first >> _end.second;
        monsters.push_back(new Monster(type, _pos, _start, _end));
    }


    map_file.close();
}

void GameMap::render() {
    renderBackground();
    renderSurface();
    renderPlayer();
    renderCherry();
    renderSpikes();
    renderClosedDoor();
    renderPlate();
    renderBox();
    renderMonster();
    renderPrincess();
    renderJump();
    renderTreasure();
    renderLevel();
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
    if (player->delPlayer == false) {
        player->render();
    }
}

void GameMap::renderCherry(){
    for (auto& cherry: cherries){
        cherry->render();
    }
}

void GameMap::renderSpikes() {
    for (auto& spike: spikes){
        spike->render();
    }
}

void GameMap::renderClosedDoor() {
    closedDoor->render();
}

void GameMap::renderPlate() {
     for (auto& plate: plates){
        plate->render();
    }
}

void GameMap::renderBox() {
     for (auto& box: boxes){
        box->render();
    }
}

void GameMap::renderMonster() {
    for (auto& monster: monsters) {
        if(!monster->deleteBot) monster->render();
    }
}

void GameMap::renderPrincess() {
    princess->render();
}

void GameMap::renderJump() {
     for (auto& jump: jumps){
        jump->render();
    }
}

void GameMap::renderTreasure() {
    for (auto& treasure: treasures) {
        treasure->render();
    }
}

void GameMap::renderLevel() {
    if(level != nullptr) level->render();
}

void GameMap::update(const Uint32& deltaTime) {
    setCollisionSurfacePlayer(surface, player, width, height);
    setCollisionSurfaceSpikes(surface, spikes, width, height);
    setCollisionCherryPlayer(cherries, player);
    SetCollisionClosedDoorPlayer(closedDoor, player);
    SetCollisionPlatePlayer(plates, player, deltaTime);
    SetCollisionBoxPlate(boxes, plates, deltaTime);
    SetCollisionPlayerBox(boxes, player);
    SetCollisionSurfaceBox(surface, boxes, width, height);
    SetCollisionMonsterPlayer(monsters, player);
    SetCollisionPrincessPlayer(princess, player, win);
    SetCollisionJumpPlayer(jumps, player);
    SetCollisionTreasurePlyaer(treasures, player);
    SetCollisionPlayerLevel(level, player);
    setCollisionSpikesBoxes(spikes, boxes);
    //Boxes(boxes);

    updatePlayer(deltaTime);
    updateCherry(deltaTime);
    updateSpikes(deltaTime);
    updateClosedDoor(deltaTime);
    updatePlate(deltaTime);
    updateBox(deltaTime);
    updateMonster(deltaTime);
    updatePrincess(deltaTime);
    updateJump(deltaTime);
    updateTreasure(deltaTime);
    updateLevel(deltaTime);
}

void GameMap::updatePlayer(const Uint32& deltaTime) {
    if (player->delPlayer) {
        exit = player->wingame ? 1 : 2;
        return;
    }

    player->update(deltaTime);
}

void GameMap::updateCherry(const Uint32& deltaTime) {
    for (int i = 0; i < (int) (cherries.size()); i++){
        cherries[i]->update(deltaTime);
    }
}

void GameMap::updateSpikes(const Uint32& deltaTime) {
     for (auto& spike : spikes) {
		if (spike->checkPlayer(player)) {
			player->end = true;
		}
		spike->update(deltaTime);
	}
}

void GameMap::updateClosedDoor(const Uint32& deltaTime) {
    closedDoor->update(deltaTime);
}

void GameMap::updatePlate(const Uint32& deltaTime) {
     closedDoor->setOpen(false);

    for (auto& plate : plates) {
        plate->setStepped(false);
    }

    SetCollisionPlatePlayer(plates, player, deltaTime);
    SetCollisionBoxPlate(boxes, plates, deltaTime);

    bool anyPlatePressed = false;
    for (auto& plate : plates) {
        plate->update();
        if (plate->getStepped()) {
            anyPlatePressed = true;
        } else {
            closedDoor->setOpen(false);
        }
    }

    if (anyPlatePressed) {
        closedDoor->setOpen(true);
    }
}

void GameMap::updateBox(const Uint32& deltaTime) {
    for (auto& box : boxes) {
		box->update(deltaTime);
	}
}

void GameMap::updateMonster(const Uint32& deltaTime) {
     for (auto it = monsters.begin(); it != monsters.end(); ) {
        if ((*it)->deleteBot) {
            delete *it;
            it = monsters.erase(it);
        } else {
            (*it)->update(deltaTime);
            ++it;
        }
    }
}

void GameMap::updatePrincess(const Uint32& deltaTime) {
    princess->update(deltaTime);
}

void GameMap::updateJump(const Uint32& deltaTime) {
    for (auto& jump: jumps){
        jump->update(deltaTime);
    }
}

void GameMap::updateTreasure(const Uint32& deltaTime) {
    for (auto& treasure: treasures) {
        treasure->update(deltaTime);
    }
}

void GameMap::updateLevel(const Uint32& deltaTime) {
    if (level != nullptr) level->update(deltaTime);
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

void GameMap::setCollisionCherryPlayer(std::vector<Cherry*>& cherries, Player* player) {
     if (player == nullptr) {
        return;
    }

    for (auto& cherry : cherries) {
        if (cherry != nullptr && cherry->getCollision()->checkCollision(player->getCollision())) {
            if (cherry->eatCherry == 0) {
                cherry->eatCherry = 1;
                totalCherry++;
            }
        }
    }
}

void GameMap::setCollisionSurfaceSpikes(Surface** surface, std::list<Spikes*>& spikes, int& width, int& height) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Collision* surfaceCollider = surface[i][j].getCollision();
            if (!surfaceCollider) {
                continue;
            }


            for (auto& spike : spikes) {
                int collisionResult = surfaceCollider->checkCollision(spike->getCollision(), 1.0f);
                if (collisionResult == collision::top || collisionResult == collision::_top) {
                    spike->canDrop = false;
                    spike->touchGround = true;
                }
            }
        }
    }
}

void GameMap::setCollisionSpikesBoxes(std::list<Spikes*> spikes, std::list<Box*> boxes) {
    for (const auto& spike : spikes) {
        Collision* spikeCollider = spike->getCollision();

        for (auto& box : boxes) {
            Collision* boxCollider = box->getCollision();
            int collisionCheck = spikeCollider->checkCollision(boxCollider, 1.0f);

            if (collisionCheck == collision::top || collisionCheck == collision::_top) {
                box->canDrop = false;
            }
        }
    }
}

void GameMap::SetCollisionClosedDoorPlayer(ClosedDoor* closedDoor, Player* player) {
    if (closedDoor == nullptr || player == nullptr) {
		return;
	}
	if (closedDoor->checkOpen() == false){
		closedDoor->getCollision()->checkCollision(player->getCollision(), 1.0f);
	}
}

void GameMap::SetCollisionPlatePlayer(std::list<Plate*>& plates, Player* player, const Uint32& deltaTime) {
    if (!player) return;

    for (auto& plate : plates) {
        int collisionCheck = plate->checkCollision(player->getCollision(), deltaTime);

        if (collisionCheck == collision::top || collisionCheck == collision::_top) {
            player->canJump = true;
        }
    }
}

void GameMap::SetCollisionBoxPlate(std::list<Box*> boxes, std::list<Plate*> plates, const Uint32& deltaTime) {
     for (auto& plate : plates) {
        for (auto& box : boxes) {
            int collisionCheck = plate->checkCollision(box->getCollision(), deltaTime);
            if (collisionCheck == collision::top || collisionCheck == collision::_top) {
                box->canDrop = false;
            }
        }
    }
}

void GameMap::SetCollisionSurfaceBox(Surface** surface, std::list<Box*>& boxes, int& width, int& height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Collision* surfaceCollision = surface[i][j].getCollision();
            if (surfaceCollision == nullptr) continue;

            for (auto& box : boxes) {
                int collisionCheck = surfaceCollision->checkCollision(box->getCollision(), 1.0f);
                if (collisionCheck == collision::top || collisionCheck == collision::_top) {
                    box->canDrop = false;
                }
            }
        }
    }
}

void GameMap::SetCollisionPlayerBox(std::list<Box*> boxes, Player* player) {
    if (player == nullptr) {
        return;
    }

    for (auto& box : boxes) {
        int collisionCheck = box->getCollision()->checkCollision(player->getCollision(), 0.5f);

        if (collisionCheck == collision::_top || collisionCheck == collision::top) {
            player->canJump = true;
        }

        if (collisionCheck == collision::left || collisionCheck == collision::_left ||
            collisionCheck == collision::right || collisionCheck == collision::_right) {
            player->pushBox = true;
        }
    }
}

void GameMap::SetCollisionMonsterPlayer(std::list<Monster*> monsters, Player* player) {
     if (!player) return;

    for (auto& monster : monsters) {
        if (player->attack.isActive && monster->checkDeath == 0) {
            int collisionResult = player->attack.collision->checkCollision(monster->getCollision());
            if (collisionResult != 0 && collisionResult != collision::_top && collisionResult != collision::_down) {
                monster->checkDeath++;
            }
        }

        else if (!player->end && monster->checkDeath == 0 &&
                 monster->getCollision()->checkCollision(player->getCollision()) == collision::top) {
            monster->checkDeath++;
        }

        else if (monster->checkDeath == 0) {
            int collisionResult = monster->getCollision()->checkCollision(player->getCollision());
            if (collisionResult == collision::right || collisionResult == collision::left) {
                player->end = false;
                player->attack.isActive = false;
            }
        }
    }
}

void GameMap::SetCollisionPrincessPlayer(Princess* princess, Player* player, bool& wingame) {
    if (princess->getCollision()->checkCollision(player->getCollision())) {
        player->setRect({princess->getPos().first + 12.5, princess->getPos().second + 12.5});
        player->wingame = true;
        win = true;
    }
}

void GameMap::SetCollisionJumpPlayer(std::list<Jump*> jumps, Player* player) {
    if (!player) {
        return;
    }

    for (const auto& jump : jumps) {
        int checkResult = jump->getCollision()->checkCollision(player->getCollision(), 1.0f);

        if (checkResult != 0 &&
            checkResult != collision::down &&
            checkResult != collision::_down) {

            player->vel.second = -sqrt(2.0f * 981.0f * player->jumHeight * 1.7f);
            player->canJump = false;
        }
    }
}

void GameMap::SetCollisionTreasurePlyaer(std::list<Treasure*> treasures, Player* player) {
    if (!player) return;

    for (auto& treasure : treasures) {
        if (player->attack.isActive && treasure->item == 0 && player->attack.collision->checkCollision(treasure->getCollision())) {
            treasure->item++;
            totalCherry += 10;
        }
    }
}

void GameMap::SetCollisionPlayerLevel(Level* level, Player* player) {
    if (!player || !level) {
        return;
    }

    if (player->attack.isActive && level->shouldRestartStatus()) {
        if (level->colliderSwitch->checkCollision(player->attack.collision) != 0) {
            level->isOpen = !level->isOpen;
            level->statusDuration = 500;
        }
    }

    if (!level->isOpen) {
        for (auto& wall : level->_wallSegments) {
            int collisionCheck = wall.first.second->checkCollision(player->getCollision(), 1.0f);
            if (collisionCheck == collision::top || collisionCheck == collision::_top) {
                player->canJump = true;
            }
        }
    }
}

void GameMap::SetCollisionLevelBox(Level* level, std::list<Box*> boxes) {
    if (!level) {
        return;
    }

    if (level->isOpen) {
        return;
    }

    for (const auto& box : boxes) {
        for (const auto& wall : level->_wallSegments) {
            int collisionCheck = wall.first.second->checkCollision(box->getCollision(), 1.0f);
            if (collisionCheck == collision::top || collisionCheck == collision::_top) {
                box->canDrop = false;
            }
        }
    }
}
