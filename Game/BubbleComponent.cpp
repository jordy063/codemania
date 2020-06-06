#include "MiniginPCH.h"
#include "BubbleComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "CollisionComponent.h"
#include "EnemyManager.h"
#include "BubbleManager.h"
#include "EnemyObserver.h"
#include "ItemManager.h"


comps::BubbleComponent::BubbleComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp,
	std::shared_ptr<comps::CollisionComponent> pCollisionComp, std::shared_ptr<comps::SpriteComponent> pSpriteBoxComp, comps::Direction direction,int id)
	:m_pPhysicsComp(pPhysicsComp)
	, m_pBoundingBoxComp(pBoundingBoxComp)
	, m_pSpriteComp(pSpriteBoxComp)
	, m_pCollisionComp(pCollisionComp)
	, m_Direction(direction)
	, m_SpriteId(id)
	,m_GoUpTimer(0)
	,m_GoUpTime(2.0f)
	, m_LifeTime(10)
	, m_EnemyId(-1)

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
		m_pPhysicsComp->SetMovement(m_Direction, BubbleManager::GetInstance().GetBubbleSpeed().x);
		m_pSpriteComp->SetBeginEndFrames(m_SpriteId * 8, 7 + m_SpriteId * 8);
		speedSet = true;
	}
	
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	//here we can check if the bullet overlaps an enemy and set the sprite to the right row

	//call a function of the enemy manager which takes a rectangle/boundingbox
	int index{};
	//if enemy is hit
	if (m_HasHitEnemy == false)
	{
		int enemyId = EnemyManager::GetInstance().CheckIfHit(m_pBoundingBoxComp, index, m_Enemy);
		if (enemyId != -1)
		{
			//this should be according to the type of enemy
			m_pSpriteComp->SetBeginEndFrames(16 + index * 8, 24 + 8 * index);
			m_pPhysicsComp->SetSpeedX(0);
			m_pPhysicsComp->SetGravity(false);
			m_pPhysicsComp->SetMovement(comps::Direction::UP, BubbleManager::GetInstance().GetBubbleSpeed().y);
			//change the sprite + physicscomp and add the collision
			m_HasHitEnemy = true;

			
			m_EnemyId = enemyId;
		}
	}
	//checks if the bullet should go up
	m_GoUpTimer += elapsedSecs;
	if (m_GoUpTimer > m_GoUpTime&& m_IsTimerReached == false)
	{
		m_pPhysicsComp->SetSpeedX(0);
		m_pPhysicsComp->SetGravity(false);
		m_pPhysicsComp->SetMovement(comps::Direction::UP, BubbleManager::GetInstance().GetBubbleSpeed().y);
		BubbleManager::GetInstance().AddBoundingBoxToList(m_pCollisionComp, m_pBoundingBoxComp);
		m_IsTimerReached = true;
	}


	//if nothing is hit
	if (m_HasHitEnemy == false)
	{
		for (int playerId{}; playerId < 2; ++playerId)
		{
			switch (BubbleManager::GetInstance().CheckIfHit(m_pBoundingBoxComp, playerId))
			{
			case HitType::UPHIT:
				BubbleManager::GetInstance().MovePlayerWithBullet(playerId);
				break;
			case HitType::SIDEHIT:
				if (m_IsTimerReached)
					m_LifeTime = 0;
				break;
			default:
				break;
			}
		}
		
		if (m_GoUpTimer > m_LifeTime)
		{
			BubbleManager::GetInstance().RemoveBullet(m_pCollisionComp, m_pBoundingBoxComp);
		}

	}
	else
	{
		if (BubbleManager::GetInstance().CheckIfHit(m_pBoundingBoxComp, m_SpriteId))
		{
			//spawn item
			//spriteid will be the type of the enemy
			ItemType type = static_cast<ItemType>(m_EnemyId);
			ItemManager::GetInstance().makeItem(m_pPhysicsComp->GetTransform()->GetPosition(), type,m_SpriteId);
			BubbleManager::GetInstance().RemoveBullet(m_pCollisionComp, m_pBoundingBoxComp);
			
		}
	}

	
	//check if bullet overlaps with enemy. if so we change our sprite,clear the enemy,make him go up and add them to the list(maybe with bool) if the bool is true we can fill up a list in the bulletmanager and then whenever an enemy is hit 
	//also check if the bullet reached travel time. if so we add the bullet to the list and make him go up



	//if the bullet has an enemy and player comes near it we call the enemyManagerDowncounter and remove the bullet
}
