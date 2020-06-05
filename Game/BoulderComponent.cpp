#include "MiniginPCH.h"
#include "BoulderComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

comps::BoulderComponent::BoulderComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp)
	:m_pPhysicsComp(pPhysicsComp)
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
	}
}
