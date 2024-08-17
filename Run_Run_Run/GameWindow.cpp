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
        }
    }
    return isRunning;
}

void GameWindow::setUp() {
    checkRunning = true;
    _totalHearts = 3;
    totalCherry = 0;

    mainMap = new GameMap();
    mainMap->loadMap("Data//Map//Map1.txt");
    background = new GameObject();
    if (background->loadIMG("Data/Textures/Background/Background1.png")) {
        background->setRect({0, 0});
        background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    }


    loose = new GameObject();
    loose->loadFromRenderedText("YOU LOSE!!!", {255, 0, 0});
    loose->setRect({410, 100});

    win = new GameObject();
    win->loadFromRenderedText("YOU WON!!!", {124, 252, 0});
    win->setRect({425, 100});

    gPause = new GameObject();
    gPause->loadFromRenderedText("GAME PAUSED!!!", {255, 255, 255});
    gPause->setRect({250, 100});

    std::string fontPath = "Data//Fonts//dlxfont_.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 20);

    nextState = new GameObject();
    nextState->loadFromRenderedText("PRESS ENTER TO RETURN MENU!", {131, 111, 255});
    nextState->setRect({200, 300});

    unpause = new GameObject();
    unpause->loadFromRenderedText("PRESS ESC TO CONTINUE OR ENTER TO RETURN MENU!", {131, 111, 255});
    unpause->setRect({50, 300});

    retry = new GameObject();
    retry->loadFromRenderedText("LET'S TRY AGAIN!", {255, 255, 255});
    retry->setRect({400, 200});

    fontPath = "Data//Fonts//dlxfont_.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 40);

}

void GameWindow::render() {
    mainMap->render();
}

void GameWindow::update(const Uint32& deltaTime) {
    if (LOOSE) return;
    if (mainMap->win && mainMap->getPlayer()->delPlayer) {
        curMap++;
        if (curMap > 5) {
            WIN = true;
        } else {
            delete mainMap;
            std::string path = "Data//Map//Map" + std::to_string(curMap) + ".txt";
            mainMap = new GameMap();
            mainMap->loadMap(path);
        }
    }
    mainMap->update(deltaTime);
}

void GameWindow::renderGameOver() {
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
    std::string fontPath = "Data//Fonts//dlxfont_.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 30);


    win = new GameObject();
    std::string winstring = "You have surpassed ";
    winstring += " players!";
    winGame->loadFromRenderedText(winstring, {255, 255, 255});
    winGame->setRect({250, 200});

    fontPath = "Data//Fonts//dlxfont_.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 40);

    background->render(false);
    win->render(false);
    winGame->render(false);
    nextState->render(false);
}

void GameWindow::free() {
    totalCherry = 0;
    curMap = 1;
}
