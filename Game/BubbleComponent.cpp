#include "MiniginPCH.h"
#include "BubbleComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "EnemyManager.h"
#include "BulletManager.h"


comps::BubbleComponent::BubbleComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp, std::shared_ptr<comps::SpriteComponent> pSpriteBoxComp, comps::Direction direction,int id)
	:m_pPhysicsComp(pPhysicsComp)
	, m_pBoundingBoxComp(pBoundingBoxComp)
	, m_pSpriteComp(pSpriteBoxComp)
	, m_BulletSpeed(30.f)
	, m_Direction(direction)
	, m_SpriteId(id)
	,m_GoUpTimer(0)
	,m_GoUpTime(2.0f)
	
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

	//call a function of the enemy manager which takes a rectangle/boundingbox
	int index{};
	if (m_HasHitEnemy == false)
	{
		if (EnemyManager::GetInstance().CheckIfHit(m_pBoundingBoxComp, index))
		{
			//this should be according to the type of enemy
			m_pSpriteComp->SetBeginEndFrames(16 + index * 8, 24 + 8 * index);
			m_pPhysicsComp->SetSpeedX(0);
			m_pPhysicsComp->SetGravity(false);
			m_pPhysicsComp->SetMovement(comps::Direction::UP, m_BulletSpeed / 2);
			//change the sprite + physicscomp and add the collision
			m_HasHitEnemy = true;
		}
	}
	m_GoUpTimer += elapsedSecs;
	if (m_GoUpTimer > m_GoUpTime && m_IsTimerReached == false)
	{
		m_pPhysicsComp->SetSpeedX(0);
		m_pPhysicsComp->SetGravity(false);
		m_pPhysicsComp->SetMovement(comps::Direction::UP, m_BulletSpeed / 2);
		BulletManager::GetInstance().AddBoundingBoxToList(m_pBoundingBoxComp);
		m_IsTimerReached = true;
	}


	//check if bullet overlaps with enemy. if so we change our sprite,clear the enemy,make him go up and add them to the list(maybe with bool) if the bool is true we can fill up a list in the bulletmanager and then whenever an enemy is hit 
	//also check if the bullet reached travel time. if so we add the bullet to the list and make him go up
}
