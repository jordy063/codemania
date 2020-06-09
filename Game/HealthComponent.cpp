#include "MiniginPCH.h"
#include "HealthComponent.h"

comps::HealthComponent::HealthComponent(int health)
	:m_Health(health)
	, m_StartHealth(health)
	, m_InvinsibleTime(2)
	, m_InvinsibleTimer(0)
{
}

void comps::HealthComponent::DropHealth(int amount)
{
	if (m_Health > 0 && m_IsInvisble == false)
	{
		m_Health -= amount;
		m_IsInvisble = true;
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

	if (m_IsInvisble)
	{
		m_InvinsibleTimer += elapsedSecs;
		if (m_InvinsibleTimer > m_InvinsibleTime)
		{
			m_InvinsibleTimer = 0;
			m_IsInvisble = false;
		}

	}
}
