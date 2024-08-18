#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <list>

#include "GameObject.hpp"
#include "Surface.hpp"
#include "Player.hpp"
#include "Cherry.hpp"
#include "Spikes.hpp"
#include "ClosedDoor.hpp"
#include "Plate.hpp"
#include "Box.hpp"
#include "Monster.hpp"
#include "Princess.hpp"
#include "Jump.hpp"
#include "Treasure.hpp"
#include "Level.hpp"

class GameMap
{
public:
    GameMap();
    ~GameMap();

    void loadMap(std::string path);
    void render();
    void renderBackground();
    void renderSurface();
    void renderPlayer();
    void renderCherry();
    void renderSpikes();
    void renderClosedDoor();
    void renderPlate();
    void renderBox();
    void renderMonster();
    void renderPrincess();
    void renderJump();
    void renderTreasure();
    void renderLevel();

    void update(const Uint32& deltaTime);
    void updatePlayer(const Uint32& deltaTime);
    void updateCherry(const Uint32& deltaTime);
    void updateSpikes(const Uint32& deltaTime);
    void updateClosedDoor(const Uint32& deltaTime);
    void updatePlate(const Uint32& deltaTime);
    void updateBox(const Uint32& deltaTime);
    void updateMonster(const Uint32& deltaTime);
    void updatePrincess(const Uint32& deltaTime);
    void updateJump(const Uint32& deltaTime);
    void updateTreasure(const Uint32& deltaTime);
    void updateLevel(const Uint32& deltaTime);

    void setCollisionSurfacePlayer(Surface** surface, Player* player, int& width, int& height);
    void setCollisionCherryPlayer(std::vector<Cherry*>& cherries, Player* player);
    void setCollisionSurfaceSpikes(Surface** ground, std::list<Spikes*>& spikes, int& width, int& height);
    void setCollisionSpikesBoxes(std::list<Spikes*> spikes, std::list<Box*> boxes);
    void SetCollisionClosedDoorPlayer(ClosedDoor* closedDoor, Player* player);
    void SetCollisionPlatePlayer(std::list<Plate*>& plates, Player* player, const Uint32& deltaTime);
    void SetCollisionPlayerBox(std::list<Box*> boxes, Player* player);
    void SetCollisionBoxPlate(std::list<Box*> boxes, std::list<Plate*> plates, const Uint32& deltaTime);
    void SetCollisionSurfaceBox(Surface** surface, std::list<Box*>& boxes, int& width, int& height);
    void Boxes(std::list<Box*> boxes);
    void SetCollisionMonsterPlayer(std::list<Monster*> monsters, Player* player);
    void SetCollisionPrincessPlayer(Princess* princess, Player* player, bool& wingame);
    void SetCollisionJumpPlayer(std::list<Jump*> jumps, Player* player);
    void SetCollisionTreasurePlyaer(std::list<Treasure*> treasures, Player* player);
    void SetCollisionPlayerLevel(Level* level, Player* player);
    void SetCollisionLevelBox(Level* level, std::list<Box*> boxes);

    Player* getPlayer() { return player; }

    bool win;
    int exit = 0;

private:
    int width, height;
    GameObject* background;
    Surface** surface;

    std::vector<Cherry*> cherries;
    std::list<Spikes*> spikes;
    std::list<Plate*> plates;
    std::list<Box*> boxes;
    std::list<Monster*> monsters;
    std::list<Jump*> jumps;
    std::list<Treasure*> treasures;

    Player* player;
    ClosedDoor* closedDoor;
    Princess* princess;
    Level* level;
};
