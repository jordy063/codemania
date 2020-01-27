#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"


comps::TextureComponent::TextureComponent(const std::string& filename)
	:m_Offset{0,0}
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

comps::TextureComponent::TextureComponent()
	: m_Offset{ 0,0 }
{
}


comps::TextureComponent::~TextureComponent()
{
	
}

void comps::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	
}

void comps::TextureComponent::SetOffset(float2 offset)
{
	m_Offset = offset;
}

void comps::TextureComponent::SetAlignment(HAlign hAlign, VAlign vAlign)
{
	m_Alignment.first = hAlign;
	m_Alignment.second = vAlign;
}

void comps::TextureComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::TextureComponent::Update(const dae::Scene & scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
}

void comps::TextureComponent::Render(const dae::Scene & scene, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	if (m_pTexture != nullptr)
	{

		auto texSize = m_pTexture->GetSize();
		int xShift = int(m_Offset.x) + (texSize.first * (int)m_Alignment.first) / 2;
		int yShift = int(m_Offset.y) + (texSize.second * (int)m_Alignment.second) / 2;
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - xShift, pos.y - yShift);
	}
}
