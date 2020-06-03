#include "MiniginPCH.h"
#include "ScorePopUpComponent.h"
#include "PhysicsComponent.h"
#include "ScoreBoard.h"
#include "ScorePopUpManager.h"

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
	if (m_OriginalPosition.y - m_pPhysicsComp->GetTransform()->GetPosition().y > m_TravelDistance)
	{
		ScoreBoard::GetInstance().AddScore(100 + m_ItemType * 100);
		ScorePopUpManager::GetInstance().RemoveScorePopUp(m_pPhysicsComp->GetTransform());
	}

}
