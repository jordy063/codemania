#include "MiniginPCH.h"
#include "ScorePopUpComponent.h"
#include "PhysicsComponent.h"
#include "ScoreBoard.h"
#include "ScorePopUpManager.h"
#include "EnemyObserver.h"
#include "SoundManager2.h"

comps::ScorePopUpComponent::ScorePopUpComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp,ItemType itemType)
	:m_pPhysicsComp(pPhysicsComp)
	, m_TravelDistance(10)
	, m_ItemType(itemType)
{
	m_OriginalPosition = m_pPhysicsComp->GetTransform()->GetPosition();
}

void comps::ScorePopUpComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	
}

void comps::ScorePopUpComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	//in the manager we already set a velocity
	//we check if the scorePopUp is at the location requested
	if (m_OriginalPosition.y - m_pPhysicsComp->GetTransform()->GetPosition().y > m_TravelDistance)
	{
		switch (m_ItemType)
		{
		case FRIES:
			ScoreBoard::GetInstance().AddScore(100);
			break;
		case MELON:
			ScoreBoard::GetInstance().AddScore(200);
			break;
		case BANANA:
			ScoreBoard::GetInstance().AddScore(500);
			break;
		default:
			break;
		}
		//in the itemComponent we only count it down when the timer expires and not when we pick it up
		//counting down when we get obtain just score just felt better to me
		EnemyObserver::GetInstance().DownCounter();
		
		ScorePopUpManager::GetInstance().RemoveScorePopUp(m_pPhysicsComp->GetTransform());
	}

}
