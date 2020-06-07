#include "MiniginPCH.h"
#include "HealthComponent.h"

comps::HealthComponent::HealthComponent(int health)
	:m_Health(health)
	, m_StartHealth(health)
{
}

void comps::HealthComponent::DropHealth(int amount)
{
	if (m_Health > 0)
	{
		m_Health -= amount;
	}
}

void comps::HealthComponent::ResetHealth()
{
	m_Health = m_StartHealth;
}

void comps::HealthComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::HealthComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
}
