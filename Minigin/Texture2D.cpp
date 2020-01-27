#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}

std::pair<int, int> dae::Texture2D::GetSize() const
{
	int w;
	int h;
	SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);

	return std::pair<int, int>(w,h);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return mTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}
