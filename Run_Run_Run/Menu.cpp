#include "Menu.hpp"

Menu::~Menu()
{
    if (bg != nullptr){
        delete bg;
    }
    if (mainGame != nullptr){
        delete mainGame;
    }
    if (instruction != nullptr){
        delete instruction;
    }
    if (exit != nullptr){
        delete exit;
    }
    if (gName != nullptr){
        delete gName;
    }
    if (currKeyStates != nullptr){
        delete currKeyStates;
    }
}

void Menu::init() {
    currState = -1;
    timeClick = 0;

    bg = new GameObject();
    bg->loadIMG("Data//Textures//Background//Background1.png");
    bg->setRect({0, 0});
    bg->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});

    std::string fontPath = "ata//Fonts//dlxfont.tff";
    font = TTF_OpenFont(fontPath.c_str(), 150);
    gName = new GameObject();
    gName->loadFromRenderedText("RUN RUN RUN", {255, 255, 255});
    gName->setRect({300, 100});

    fontPath = "ata//Fonts//dlxfont.tff";
    font = TTF_OpenFont(fontPath.c_str(), 40);

    mainGame = new GameObject();
    mainGame->loadFromRenderedText("PLAY", {255, 255, 255});
    mainGame->setRect({50, 350});

    instruction = new GameObject();
    instruction->loadFromRenderedText("INSTRUCTION", {255, 255, 255});
    instruction->setRect({50, 400});

    exit = new GameObject();
    exit->loadFromRenderedText("EXIT", {255, 255, 255});
    exit->setRect({50, 450});
}

int Menu::update(const Uint32& deltaTime) {
    currKeyStates = SDL_GetKeyboardState(NULL);

    if (currKeyStates[SDL_SCANCODE_DOWN] && timeClick <= 0) {
        currState = (currState + 1) % 3;
        timeClick = 200;
    }

    if (currKeyStates[SDL_SCANCODE_UP] && timeClick <= 0) {
        currState = (currState - 1 + 3) % 3;
        timeClick = 200;
    }

    if (currKeyStates[SDL_SCANCODE_RETURN] && timeClick <= 0) {
        timeClick = 200;
        return currState;
    }

    if (timeClick >= 0) {
        timeClick -= deltaTime;
    }

    updateMenuItem(mainGame, "PLAY", {255, 255, 255}, {50, 350});
    updateMenuItem(instruction, "INSTRUCTION", {255, 255, 255}, {50, 400});
    updateMenuItem(exit, "EXIT", {255, 255, 255}, {50, 450});

    switch (currState) {
        case 0:
            updateMenuItem(mainGame, ">PLAY", {255, 255, 255}, {60, 350});
            break;
        case 1:
            updateMenuItem(instruction, ">INSTRUCTION", {255, 255, 255}, {60, 400});
            break;
        case 2:
            updateMenuItem(exit, ">EXIT", {255, 255, 255}, {60, 450});
            break;
    }

    return -1;
}

void Menu::updateMenuItem(GameObject* menuItem, const std::string& text, const SDL_Color& color, std::pair<int, int> pos) {
    menuItem->loadFromRenderedText(text, color);
    menuItem->setRect(pos);
}

void Menu::render() {
    bg->render(false);
    mainGame->render(false);
    instruction->render(false);
    exit->render(false);
    gName->render(false);
}
