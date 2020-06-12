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
#include "GameInfo.h"


comps::BubbleComponent::BubbleComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp,
	std::shared_ptr<comps::CollisionComponent> pCollisionComp, std::shared_ptr<comps::SpriteComponent> pSpriteBoxComp, comps::Direction direction,int id,int playerAmount)
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
	, m_EnemyTrapTime(5)
	, m_EnemyTrapTimer()
	, m_PlayerAmount(playerAmount)
	,m_AddBoundingBoxTime(0.5f)
	, m_IsBoundingBoxTimerReached(false)
{
}

void comps::BubbleComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	
}

void comps::BubbleComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	//at the start we set the speed for the current direction
	if (speedSet == false)
	{
		m_pPhysicsComp->SetMovement(m_Direction, BubbleManager::GetInstance().GetBubbleSpeed().x);
		m_pSpriteComp->SetBeginEndFrames(m_SpriteId * 8, 7 + m_SpriteId * 8);
		speedSet = true;
	}
	
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);


	int index{};
	//if enemy is hit
	if (m_HasHitEnemy == false)
	{
		//here we can check if the bullet overlaps an enemy and set the sprite to the right row
		int enemyId = EnemyManager::GetInstance().CheckIfHit(m_pBoundingBoxComp, index, m_Enemy);
		m_EnemyType = static_cast<EnemyType>(enemyId);
		if (enemyId != -1)
		{
			//we change the sprite according to the enemy type
			m_pSpriteComp->SetBeginEndFrames(16 + index * 8, 24 + 8 * index);
			m_pPhysicsComp->SetSpeedX(0);
			m_pPhysicsComp->SetGravity(false);
			m_pPhysicsComp->SetMovement(comps::Direction::UP, BubbleManager::GetInstance().GetBubbleSpeed().y);
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
	//checks if bullet should get it's boundingbox
	if (m_GoUpTimer > m_AddBoundingBoxTime && m_IsBoundingBoxTimerReached == false)
	{
		BubbleManager::GetInstance().AddBoundingBoxToList(m_pCollisionComp, m_pBoundingBoxComp);
		m_IsBoundingBoxTimerReached = true;
	}


	//if nothing is hit
	if (m_HasHitEnemy == false)
	{
		//only in multiplayer both players can collide with bubbles
		if (GameInfo::GetInstance().GetGameMode() != GameMode::MULTIPLAYER)
		{
			m_PlayerAmount = 1;
		}

		//depending on where the player hits he can write or pop a bubble
		for (int playerId{}; playerId < m_PlayerAmount; ++playerId)
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
		
		//if the lifetime is up we delete the bullet
		if (m_GoUpTimer > m_LifeTime)
		{
			BubbleManager::GetInstance().RemoveBullet(m_pCollisionComp, m_pBoundingBoxComp);
		}

	}
	else
	{
		//here an enemy was hit
		//if the player hits the bubble we spawn an item according to the enemy type
		if (BubbleManager::GetInstance().CheckIfHit(m_pBoundingBoxComp, m_SpriteId))
		{
			//spawn item + remove bullet
			ItemType type = static_cast<ItemType>(m_EnemyId);
			ItemManager::GetInstance().makeItem(m_pPhysicsComp->GetTransform()->GetPosition(), type,m_SpriteId);
			m_Enemy->Clear();
			BubbleManager::GetInstance().RemoveBullet(m_pCollisionComp, m_pBoundingBoxComp);
			
		}

		//if the enemy is trapped for too long it gets free
		m_EnemyTrapTimer += elapsedSecs;
		if (m_EnemyTrapTimer > m_EnemyTrapTime)
		{
			m_EnemyTrapTimer = 0;
			m_HasHitEnemy = false;
			m_Enemy->Enable();
			m_Enemy->GetTransform()->Translate(m_pPhysicsComp->GetTransform()->GetPosition());
			EnemyManager::GetInstance().AddEnemyToList({ m_Enemy,m_EnemyType });
			BubbleManager::GetInstance().RemoveBullet(m_pCollisionComp, m_pBoundingBoxComp);
		}
	}

}
