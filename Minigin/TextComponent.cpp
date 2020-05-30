#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"


comps::TextComponent::TextComponent( std::shared_ptr<dae::Font> font,float width, float height, SDL_Color color)
	:m_pFont(font)
	,TextureComponent(width,height)
	,m_Color(color)
	,m_Text("")
{
}

comps::TextComponent::~TextComponent()
{
	
}


void comps::TextComponent::SetText(std::string text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void comps::TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}

void comps::TextComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::TextComponent::Update(const dae::Scene & scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<dae::Texture2D>(texture);
	}
}

