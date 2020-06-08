#include "MiniginPCH.h"
#include "BoulderComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoulderManager.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "LevelManager.h"

comps::BoulderComponent::BoulderComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox,
	std::vector<std::shared_ptr<comps::HealthComponent>> pPlayerHealthComps)
	:m_pPhysicsComp(pPhysicsComp)
	, m_pBoundingBox(pBoundingBox)
	,m_pPlayerHealthComps(pPlayerHealthComps)
{
}

void comps::BoulderComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::BoulderComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	//check if it hits a wall on the side.

	if (m_pPhysicsComp->GetVelocity().x == 0)
	{
		//delete the boulder
		BoulderManager::GetInstance().RemoveBoulder(m_pPhysicsComp->GetTransform());
	}

	for (int i{}; i < m_pPlayerHealthComps.size(); ++i)
	{
		if (BoulderManager::GetInstance().CheckIfHit(m_pBoundingBox, i))
		{
			m_pPlayerHealthComps[i]->DropHealth(1);
			LevelManager::GetInstance().ResetPlayerPos(i);
		}
	}
}
