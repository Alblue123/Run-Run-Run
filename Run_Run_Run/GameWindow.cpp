#include "GameWindow.hpp"

GameWindow::GameWindow()
{
    mTexture = NULL;
    rect = { 0, 0, 0 , 0 };
}

GameWindow::~GameWindow()
{
    free();
}
bool GameWindow::loadIMG(std::string path, SDL_Renderer* screen)
{
    free(); //free pre-existed objects

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface == NULL)
    {
        std::cout << "Unable to load image! SDL_image Error:" << path << ", " << IMG_GetError() << std::endl;
    }
    else
    {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (newTexture == NULL)
        {
            std::cout << "Unable to create texture from: " << path << ", " << SDL_GetError() << std::endl;
        }
        else
        {
            rect.w = loadSurface->w;
            rect.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    mTexture = newTexture;

    return mTexture != NULL;
}

void GameWindow::render(SDL_Renderer* renderer, const SDL_Rect* clip)
{
    SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

    if (clip != NULL)
    {
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }
    SDL_RenderCopy(renderer, mTexture, clip, &renderquad);
}

void GameWindow::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}

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
    gWindow = SDL_CreateWindow("Run Run Run", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cout << "Window could not be created! SDL Error:" << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else
    {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL)
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 88, 128, 204, 255);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << std::endl;
                isRunning = false;
            }
        }
    }
    return isRunning;
}
