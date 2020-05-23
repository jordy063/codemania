#pragma once
#include "TextureComponent.h"
#include <string>
#include <SDL_pixels.h>

namespace dae
{
	class Font;
	class Texture2D;
}

namespace comps
{
	


	class TextComponent : public comps::TextureComponent
	{
	public:

		TextComponent(const std::string& text, std::shared_ptr<dae::Font> font,float width, float height, SDL_Color color);
		virtual ~TextComponent();


		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void SetText(std::string text);
		void SetColor(SDL_Color color);

	protected:
		void Initialize(const dae::Scene& scene) override;
		void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;


	private:
		std::string m_Text;
		SDL_Color m_Color;
		std::shared_ptr<dae::Font> m_pFont;
	};
}

