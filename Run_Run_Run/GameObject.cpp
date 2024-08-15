#include "GameObject.hpp"

GameObject::GameObject()
{
    mTexture = NULL;
    rect = { 0, 0, 0 , 0 };
}

GameObject::~GameObject()
{
    free();
}

void GameObject::movePos(std::pair<int, int> pos) {
    rect.x += pos.first;
    rect.y += pos.second;
}

bool GameObject::loadIMG(std::string path)
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
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
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

void GameObject::loadFromRenderedText(TTF_Font* font, SDL_Color textColor) {
    free();

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (text_surface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
		if (mTexture == NULL)
		{
			std::cout
				<< "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			width_ = text_surface->w;
			height_ = text_surface->h;
		}

		SDL_FreeSurface(text_surface);
	}

	return mTexture != NULL;
}

void GameObject::render(bool flip, SDL_Rect* clip, double angle, SDL_Point* center){
	if (flip){
		SDL_RenderCopyEx(renderer, mTexture, clip, &rect, angle, center, SDL_FLIP_HORIZONTAL);
	}
	else{
		SDL_RenderCopyEx(renderer, mTexture, clip, &rect, angle, center, SDL_FLIP_NONE);
	}
}

void GameObject::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}
