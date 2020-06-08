#pragma once
#include "Singleton.h"
#include "structs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTextureCutOut(const Texture2D& texture, float x, float y,rectangle_ srcRect) const;
		void RenderTextureCutOut(const Texture2D& texture, const float x, const float y, rectangle_ srcRect, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

