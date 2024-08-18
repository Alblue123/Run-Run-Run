#include "GameWindow.hpp"



GameWindow::GameWindow() {
    mainMap = nullptr;
    checkRunning = false;
}

GameWindow::~GameWindow() {}


bool GameWindow::init() {
     bool isRunning = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Set texture filtering to linear
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //create window
    window = SDL_CreateWindow("Run Run Run", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL Error:" << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(renderer, 88, 128, 204, 255);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << std::endl;
                isRunning = false;
            }

            if (TTF_Init() == -1)
            {
                std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                isRunning = false;
            }
            font = TTF_OpenFont("Data//Fonts//dlxfont_.ttf", 30);
            if (font ==  nullptr) {
                std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
            }

            if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                std::cerr << "Failed to load font! MIX_Error: " << Mix_GetError() << std::endl;
            }
        }
    }

    eatCherry = Mix_LoadWAV("Data//Sounds//eat.wav");
    mushroom = Mix_LoadWAV("Data//Sounds//mushroom.wav");
    slash = Mix_LoadWAV("Data//Sounds//slash.wav");
    jump = Mix_LoadWAV("Data//Sounds//jump.wav");
    teleport = Mix_LoadWAV("Data//Sounds//teleport.wav");
    winG = Mix_LoadWAV("Data//Sounds//win.wav");
    lost = Mix_LoadWAV("Data//Sounds//lost.wav");
    death = Mix_LoadWAV("Data//Sounds//death.wav");
    push = Mix_LoadWAV("Data//Sounds//push.wav");

    game = Mix_LoadMUS("Data//Sounds//game.wav");
    menuG = Mix_LoadMUS("Data//Sounds//menu.wav");


    return isRunning;
}

void GameWindow::setUp() {
    checkRunning = true;
    _totalHearts = 3;
    totalCherry = 0;

    mainMap = new GameMap();
    mainMap->loadMap("Data//Map//Map1.txt");

    cherry1 = new GameObject();
    cherry1->loadIMG("Data//Textures//Background//cherry.png");
    cherry1->setSize({40, 40});
    cherry1->setRect({20, 10});
    cherry2 = new GameObject();
    cherry2->loadFromRenderedText("x0", {255, 255, 255});
    cherry2->setRect({70, 20});

    heart1 = new GameObject();
    heart1->loadIMG("Data//Textures//Background//heart.png");
    heart1->setSize({40, 40});
    heart1->setRect({900, 10});
    heart2 = new GameObject();
    heart2->loadFromRenderedText("x3", {255, 255, 255});
    heart2->setRect({940, 15});

    background = new GameObject();
    if (background->loadIMG("Data/Textures/Background/Background1.png")) {
        background->setRect({0, 0});
        background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    }


    loose = new GameObject();
    loose->loadFromRenderedText("YOU LOSE!!!", {255, 0, 0});
    loose->setRect({300, 100});

    win = new GameObject();
    win->loadFromRenderedText("YOU WON!!!", {124, 252, 0});
    win->setRect({300, 100});

    gPause = new GameObject();
    gPause->loadFromRenderedText("GAME PAUSED!!!", {255, 255, 255});
    gPause->setRect({250, 100});

    std::string fontPath = "Data//Fonts//dlxfont_.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 20);

    nextState = new GameObject();
    nextState->loadFromRenderedText("PRESS ENTER TO RETURN MENU!", {131, 111, 255});
    nextState->setRect({250, 300});

    unpause = new GameObject();
    unpause->loadFromRenderedText("PRESS ESC TO CONTINUE OR ENTER TO RETURN MENU!", {131, 111, 255});
    unpause->setRect({50, 300});

    retry = new GameObject();
    retry->loadFromRenderedText("LET'S TRY AGAIN!", {255, 255, 255});
    retry->setRect({350, 200});

    fontPath = "Data//Fonts//dlxfont_.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 30);

}

void GameWindow::render() {
    mainMap->render();
    cherry1->render(false);
    cherry2->render(false);
    heart1->render(false);
    heart2->render(false);
}

void GameWindow::update(const Uint32& deltaTime) {
    if (LOOSE) return;
    if (mainMap->win && mainMap->getPlayer()->delPlayer) {
        curMap++;
        if (curMap > 1) {
            WIN = true;
        } else {
            delete mainMap;
            std::string path = "Data//Map//Map" + std::to_string(curMap) + ".txt";
            mainMap = new GameMap();
            mainMap->loadMap(path);
        }
    }

    mainMap->update(deltaTime);

    if (_totalHearts <= 0) LOOSE = true;
    else {
        heart2->loadFromRenderedText("x" + std::to_string(_totalHearts), {255, 255, 255});
    }
    cherry2->loadFromRenderedText("x" + std::to_string(totalCherry), {255, 255, 255});
}

void GameWindow::renderGameOver() {
    Mix_PlayChannel(-1, lost, 0);
    background->render(false);
    loose->render(false);
    retry->render(false);
    nextState->render(false);
}

void GameWindow::renderPause() {
    background->render(false);
    gPause->render(false);
    unpause->render(false);
}

void GameWindow::renderWin() {
    Mix_PlayChannel(-1, winG, 0);
    background->render(false);
    win->render(false);
    nextState->render(false);
}

void GameWindow::free() {
    totalCherry = 0;
    curMap = 1;
}
