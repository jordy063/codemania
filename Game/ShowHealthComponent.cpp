#include "MiniginPCH.h"
#include "ShowHealthComponent.h"
#include "ScoreBoard.h"
#include "HealthComponent.h"

comps::ShowHealthComponent::ShowHealthComponent(std::shared_ptr<dae::Font> font, float width, float height, SDL_Color color, std::shared_ptr<comps::HealthComponent> pHealthComp)
	:comps::TextComponent(font,width,height,color)
	,m_pHealthComp(pHealthComp)
{
}
void comps::ShowHealthComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	m_AllowScrolling = false;
}

void comps::ShowHealthComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);
	int health{ m_pHealthComp->GetHealth() };

	if (m_Health != health)
	{
		m_Health--;
		SetText("health: " + std::to_string(health));
	}

	TextComponent::Update(scene, elapsedSecs, pos);
}