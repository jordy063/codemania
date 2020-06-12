#include "MiniginPCH.h"
#include "PlayerVersusComponent.h"
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "BubbleManager.h"
#include "LevelManager.h"

comps::PlayerVersusComponent::PlayerVersusComponent(std::shared_ptr<dae::GameObject> pPlayer1, std::shared_ptr < comps::BoundingBoxComponent> pEnemyPlayerBoundingBox,
	std::shared_ptr < comps::HealthComponent> pEnemyPlayerHealthComp)
{
	//register te components needed during the game
	
	auto boundingBoxComp = pPlayer1->GetComponent(ComponentType::BOUNDINGBOXCOMP);
	m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

	auto healthComp = pPlayer1->GetComponent(ComponentType::HEALTHCOMPONENT);
	m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));

	m_pPlayerBoundingBoxes.push_back(pEnemyPlayerBoundingBox);
	m_pPlayerHealthComps.push_back(pEnemyPlayerHealthComp);
	
}

void comps::PlayerVersusComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::PlayerVersusComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

	//if player2 hits a bullet we do damage
	if (BubbleManager::GetInstance().CheckPlayer2HitsBullet())
	{
		m_pPlayerHealthComps[1]->DropHealth(1);
		
	}

	//check if the player1 overlaps with player2. if so do damage to player 1 and put him in his corner
	if (m_pPlayerBoundingBoxes[0]->IsOverlapping(m_pPlayerBoundingBoxes[1]))
	{
		m_pPlayerHealthComps[0]->DropHealth(1);
	}
}
