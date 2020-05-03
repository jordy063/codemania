#include "MiniginPCH.h"
#include "BubbleComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"

comps::BubbleComponent::BubbleComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp, std::shared_ptr<comps::SpriteComponent> pSpriteBoxComp, comps::Direction direction,int id)
	:m_pPhysicsComp(pPhysicsComp)
	, m_pBoundingBoxComp(pBoundingBoxComp)
	, m_pSpriteComp(pSpriteBoxComp)
	, m_BulletSpeed(30.f)
	, m_Direction(direction)
	, m_SpriteId(id)
{
}

void comps::BubbleComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	
}

void comps::BubbleComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	if (speedSet == false)
	{
		m_pPhysicsComp->SetMovement(m_Direction, m_BulletSpeed);
		m_pSpriteComp->SetBeginEndFrames(m_SpriteId * 8, 7 + m_SpriteId * 8);
		speedSet = true;
	}
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	//here we can check if the bullet overlaps an enemy and set the sprite to the right row
}
