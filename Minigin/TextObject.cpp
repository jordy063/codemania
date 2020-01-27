#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextObject::TextObject(const std::string& text, std::shared_ptr<Font> font) 
	: mNeedsUpdate(true), mText(text), mFont(font), mTexture(nullptr),m_Alignment(HAlign::LEFT,VAlign::TOP)
{ 
	m_pTransform = new TransformComponent();
}

dae::TextObject::~TextObject()
{
	delete m_pTransform;

}

void dae::TextObject::Update(float elapsedSecs)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	if (mNeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextObject::Render() const
{
	if (mTexture != nullptr)
	{
		const auto pos = m_pTransform->GetPosition();
		auto texSize = mTexture->GetSize();
		int xShift = (texSize.first * (int)m_Alignment.first) / 2;
		int yShift = (texSize.second * (int)m_Alignment.second) / 2;
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x - xShift, pos.y - yShift);
	}
}

void dae::TextObject::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_pTransform->Translate(x, y);
}

void dae::TextObject::SetAlignment(HAlign hAlign, VAlign vAlign)
{
	m_Alignment.first = hAlign;
	m_Alignment.second = vAlign;
}


