#include "Game.hpp"
#include "GameWindow.hpp"


GameWindow* gWin = new GameWindow();
SDL_Window* window;
SDL_Renderer* renderer;

extern const int FPS;
extern const int frameDelay;
Uint32 frameStart;
unsigned int frameTime;

bool HandleEvents(bool& quitGame);
void renderGame();
int play();


enum Menu{
	PLAYGAME,
	INSTRUCTION,
	EXIT,
	MENU
};

void start() {
    if(gWin->init()) {
        int type = PLAYGAME;
        play();
    }
}

bool HandleEvents(bool& quitGame) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quitGame = true;
            return true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    break;
                case SDLK_RETURN:
                    break;
                default:
                    break;
            }
        }
    }
    return false;
}
void renderGame() {
    gWin->render();
}

/*void renderGame() {
    if (gWin->isWinGame()) {
        game->RenderGameWin();
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])
            return;
    } else if (game->isLoseGame()) {
        game->RenderGameOver();
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])
            return;
    } else {
        if (currentstate == 1)
            game->RenderGamePause();
        else
            game->Render();
    }
}*/

int play() {
    bool quit = false, quitGame = false;
    Uint32 start_time = 0, current_time, deltaTime;
    gWin->setUp();

    while (!quit) {
        Uint32 frameStart = SDL_GetTicks();
        SDL_RenderClear(renderer);

        current_time = SDL_GetTicks();
        deltaTime = std::min(current_time - start_time, static_cast<Uint32>(frameDelay));
        start_time = current_time;

        if (HandleEvents(quitGame)) {
            quit = true;
            break;
        }

        renderGame();

        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);

        if (quitGame)
            break;
    }

   return -1;
}
