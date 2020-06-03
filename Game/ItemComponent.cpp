#include "MiniginPCH.h"
#include "ItemComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "ItemManager.h"
#include "EnemyObserver.h"
#include "ScorePopUpManager.h"

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
	//here we ask the components we want
	
}

void comps::ItemComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	//this will probably be empty
}

void comps::ItemComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	
	if (m_HasJumped == false)
	{
		m_pPhysicsComp->SetSpeedX(15);
		m_pPhysicsComp->SetSpeedY(-250);
		m_pSpriteComp->SetBeginEndFrames(m_ItemType * 4,3 + m_ItemType * 4);
		m_HasJumped = true;
	}

	else if(m_pPhysicsComp->GetAirBorne() == false && IsLootAble == false)
	{
		m_pPhysicsComp->SetSpeedX(0);
		m_pSpriteComp->SetBeginEndFrames(10 + m_ItemType, 10 + m_ItemType);
		IsLootAble = true;

		//lower it a little bit
	}

	else if (IsLootAble)
	{

		if (ItemManager::GetInstance().CheckIfHit(m_pBoundingBoxComp))
		{
			if (m_IsDownCounterCalled == false)
			{
				EnemyObserver::GetInstance().DownCounter();
				m_IsDownCounterCalled = true;
			}
			ItemManager::GetInstance().DoEffect(m_ItemType);
			ScorePopUpManager::GetInstance().MakeScorePopUp(m_ItemType, m_SpriteId,m_pPhysicsComp->GetTransform()->GetPosition());
			ItemManager::GetInstance().RemoveItem(m_pBoundingBoxComp);

			
		}
	}
	m_NotifyTimer += elapsedSecs;
	if(m_IsDownCounterCalled == false)
	{
		if (m_NotifyTimer > m_TimeBeforeNotify)
		{
			EnemyObserver::GetInstance().DownCounter();
			m_IsDownCounterCalled = true;
		}
	}

	if (m_NotifyTimer > m_LifeTime)
	{
		ItemManager::GetInstance().RemoveItem(m_pBoundingBoxComp);
	}
	//if they bullet hits an enemy we make an item.
	//an item has a physicscomponent with gravity but we give it a certain force.
	//depending on the enemy the first frames will be the death animation of that enemy
	//if it touches the ground we change the sprite to an item and only then the player can pick it up




	//check if the player overlaps with this boundingbox

	//if so we have to place a score instead of the texture

	//after that the texture has to become unactive
}
