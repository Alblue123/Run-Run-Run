#include "Instruction.hpp"

Instruction::~Instruction()
{
    if (bg != nullptr){
        delete bg;
    }
    if (main != nullptr){
        delete main;
    }
    if (title != nullptr){
        delete title;
    }
    if (nextState != nullptr){
        delete nextState;
    }
}

void Instruction::init() {
    bg = new GameObject();
    bg->loadIMG("Data//Textures//Background//Background1.png");
    bg->setRect({0, 0});
    bg->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});

    title = new GameObject();
    title->loadFromRenderedText("Instruction", {255, 255, 255});
    title->setRect({400, 20});

    main = new GameObject();
    main->loadIMG("Data//Textures//Background//Background1.png");
    main->setRect({50, 50});

    std::string fontPath = "Data//Fonts//dlxfont.tff";
    font = TTF_OpenFont(fontPath.c_str(), 30);
    nextState = new GameObject();
    nextState->loadFromRenderedText("PRESS ENTER TO RETURN MENU!", {131, 111, 255});
    nextState->setRect({300, 500});

    fontPath = "Data//Fonts//dlxfont.tff";
    font = TTF_OpenFont(fontPath.c_str(), 40);
}

void Instruction::render() {
    bg->render(false);
    title->render(false);
    main->render(false);
    nextState->render(false);
}
