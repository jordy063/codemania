#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "LevelManager.h"


void comps::FpsComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
	m_AllowScrolling = false;
}

void comps::FpsComponent::Update(const dae::Scene & scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);

	static float m_Lag = 0;
	static float m_Frames = 0;
	m_Lag += elapsedSecs;
	m_Frames++;

	if (m_Lag >= 1)
	{

		SetText("fps: " + std::to_string(int(m_Frames)));
		m_Frames = 0;
		m_Lag -= 1;
	}

	TextComponent::Update(scene,elapsedSecs, pos);
}



