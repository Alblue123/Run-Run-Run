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
    title->setRect({300, 20});

    main = new GameObject();
    main->loadIMG("Data//Textures//Background//Tutorial.png");
    main->setRect({50, 50});

    std::string fontPath = "Data//Fonts//dlxfont_.ttf";
    font = TTF_OpenFont(fontPath.c_str(), 25);
    nextState = new GameObject();
    nextState->loadFromRenderedText("PRESS ENTER TO RETURN MENU!", {255, 255, 255});
    nextState->setRect({200, 450});

    fontPath = "Data//Fonts//dlxfont_.ttf";
    font = TTF_OpenFont(fontPath.c_str(), 40);
}

void Instruction::render() {
    bg->render(false);
    title->render(false);
    main->render(false);
    nextState->render(false);
}
