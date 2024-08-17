#pragma once

#include <SDL_ttf.h>

#include "Game.hpp"
#include "GameObject.hpp"

class Menu
{
public:
    Menu() {}
    ~Menu();

    void init();
    int update(const Uint32& deltaTime);
    void updateMenuItem(GameObject* menuItem, const std::string& text, const SDL_Color& color, std::pair<int, int> pos);
    void render();
private:
    GameObject* gName;
    GameObject* bg;
    GameObject* mainGame;
    GameObject* instruction;
    GameObject* exit;

    int currState = -1;
    int timeClick;
    const Uint8* currKeyStates;
};
