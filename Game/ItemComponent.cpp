#include "MiniginPCH.h"
#include "ItemComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "ItemManager.h"
#include "EnemyObserver.h"
#include "ScorePopUpManager.h"
#include "SoundManager2.h"

comps::ItemComponent::ItemComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::SpriteComponent> pSpriteComp,
	std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp,ItemType type,int spriteId)
	:m_pBoundingBoxComp(pBoundingBoxComp)
	,m_pPhysicsComp(pPhysicsComp)
	,m_pSpriteComp(pSpriteComp)
	,m_ItemType(type)
	, m_TimeBeforeNotify(5)
	, m_NotifyTimer(0)
	, m_LifeTime(10)
	, m_SpriteId(spriteId)
{
	
}

void comps::ItemComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::ItemComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	
	//when an enemy dies we play the right deathanimation
	if (m_HasJumped == false)
	{
		m_pPhysicsComp->SetSpeedX(m_Speed.x);
		m_pPhysicsComp->SetSpeedY(m_Speed.y);
		m_pSpriteComp->SetBeginEndFrames(m_ItemType * 4,3 + m_ItemType * 4);
		m_HasJumped = true;
	}

	//when it hits the ground we change the texture to an item
	else if(m_pPhysicsComp->GetAirBorne() == false && IsLootAble == false)
	{
		m_pPhysicsComp->SetSpeedX(0);
		m_pSpriteComp->SetBeginEndFrames(12 + m_ItemType, 12 + m_ItemType);
		IsLootAble = true;

	}

	//if the item has hit the ground we can pick it up
	else if (IsLootAble)
	{

		if (ItemManager::GetInstance().CheckIfHit(m_pBoundingBoxComp))
		{
			std::string filename{ "../Sounds/scoreSound.wav" };
			SoundManager2::GetInstance().playEffect(filename);
			ScorePopUpManager::GetInstance().MakeScorePopUp(m_ItemType, m_SpriteId,m_pPhysicsComp->GetTransform()->GetPosition());
			ItemManager::GetInstance().RemoveItem(m_pBoundingBoxComp);

			
		}
	}
	
	//when an item is picked up we start a timer and lower the enemy count
	//this is important for the enemy observer
	m_NotifyTimer += elapsedSecs;
	if(m_IsDownCounterCalled == false)
	{
		if (m_NotifyTimer > m_TimeBeforeNotify)
		{
			EnemyObserver::GetInstance().DownCounter();
			m_IsDownCounterCalled = true;
		}
	}

	//if we wait too long the item gets removed
	if (m_NotifyTimer > m_LifeTime)
	{
		ItemManager::GetInstance().RemoveItem(m_pBoundingBoxComp);
	}

}
