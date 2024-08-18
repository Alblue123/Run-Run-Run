#include "Game.hpp"
#include "GameWindow.hpp"


GameWindow* gWin = new GameWindow();
SDL_Window* window;
SDL_Renderer* renderer;
Menu* menu;
Instruction* instruction;

extern const int FPS;
extern const int frameDelay;
Uint32 frameStart;
unsigned int frameTime;

int totalCherry = 0;
int _totalHearts = 0;

TTF_Font* font;

Mix_Chunk* eatCherry;
Mix_Chunk* jump;
Mix_Chunk* slash;
Mix_Chunk* mushroom;
Mix_Chunk* push;
Mix_Chunk* winG;
Mix_Chunk* lost;
Mix_Chunk* death;
Mix_Chunk* teleport;

Mix_Music* game;
Mix_Music* menuG;


bool HandleEvents(bool& quitGame, int& currState, int& status);
void renderGame();
int play();
int main();
int instruct();
int exit();
void clean();


enum MAINSCREEN {
	PLAYGAME,
	INSTRUCTION,
	EXIT,
	MENU
};

void start() {
    if(gWin->init()) {
        int type = MENU;
        while (type != EXIT){
            gWin = new GameWindow();
            switch (type){
                case MENU:
                    type = main();
                    break;
                case INSTRUCTION:
                    type = instruct();
                    break;
                case EXIT:
                    type = exit();
                    break;
                case PLAYGAME:
                    type = play();
                    break;
                default:
                    break;
            }
            gWin->free();
            delete gWin;
            }
    }
    clean();
}

void renderGame() {
    gWin->render();
}

bool HandleEvents(bool& quitGame, int& currState, int& status) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quitGame = true;
            return true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    if (currState == -1) currState = 1;
                    else currState = -1;
                    break;
                case SDLK_RETURN:
                    if (currState == 1 && event.key.repeat == 0) {
                        status = MENU;
                        return true;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return false;
}

int renderGame(int& currState) {
    if (gWin->isWinning()) {
        Mix_HaltChannel(-1);
        gWin->renderWin();
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN]) {
            return MENU;
        }
    } else if (gWin->isLosing()) {
        gWin->renderGameOver();
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN]) {
            return MENU;
        }
    } else {
        if (currState == 1) {
            gWin->renderPause();
        } else {
            gWin->render();
        }
    }
    return 0;
}

int play() {
    bool quit = false, quitGame = false;
    int currState = -1;
    Uint32 start_time = 0, current_time, deltaTime;
    int status = 0;
    gWin->setUp();
    Mix_PlayMusic(game, -1);
    while (!quit) {
        Uint32 frameStart = SDL_GetTicks();
        SDL_RenderClear(renderer);

        current_time = SDL_GetTicks();
        deltaTime = std::min(current_time - start_time, static_cast<Uint32>(frameDelay));
        start_time = current_time;

        if (HandleEvents(quitGame, currState, status)) {
            if (status == MENU) {
                return MENU;
            }
            quit = true;
            break;
        }


        if (currState != 1) {
            gWin->update(deltaTime);
        }

        int gameState = renderGame(currState);
        if (gameState == MENU) {
            return MENU;
        }

        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);

        if (quitGame)
            break;
    }

    return -1;
}

int main() {
    menu = new Menu();
    menu->init();
    Mix_PlayMusic(menuG, -1);

    Uint32 start_time = 0, current_time, deltaTime;
	bool quit = false;
    int state = -1;

	while (!quit){
		SDL_Event event;
		frameStart = SDL_GetTicks();
		current_time = SDL_GetTicks();
		deltaTime = current_time - start_time;
		start_time = current_time;
		state = menu->update(deltaTime);
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
				return EXIT;
			}
		}
        switch (state){
            case -1:
                menu->render();
                break;
            case INSTRUCTION:
                return INSTRUCTION;
            case EXIT:
                return EXIT;
            case PLAYGAME:
                return PLAYGAME;
            default:
                break;
        }

		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
    }
    return -1;
}

int exit() {
    return EXIT;
}

int instruct() {
    instruction = new Instruction();
    instruction->init();

	Uint32 start_time = 0, current_time, deltaTime;
	bool quit = false;

    while (!quit){
		SDL_Event event;
		frameStart = SDL_GetTicks();
		current_time = SDL_GetTicks();
		deltaTime = current_time - start_time;
		start_time = current_time;
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
				return EXIT;
			}
			else{
				 if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) return MENU;
			}
		}
		instruction->render();
		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
    }
    return -1;
}

void clean() {
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
