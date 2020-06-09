#include "MiniginPCH.h"
#include "PlayerVersusComponent.h"
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "BubbleManager.h"
#include "LevelManager.h"

comps::PlayerVersusComponent::PlayerVersusComponent(std::vector<std::shared_ptr<dae::GameObject>> pPlayers)
{
	for (std::shared_ptr<dae::GameObject> pPlayerObject : pPlayers)
	{
		auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

		auto healthComp = pPlayerObject->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));
	}
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
	if (m_pPlayerHealthComps[1]->GetInvinsible() == false)
	{
		std::cout<<"invinsible over"<<'\n';
	}

	if (BubbleManager::GetInstance().CheckPlayer2HitsBullet())
	{
		m_pPlayerHealthComps[1]->DropHealth(1);
		LevelManager::GetInstance().ResetPlayerPos(1);
		
	}
	//check if the boundingbox hits any bullets.
	//if yes we do damage en put the player back in the corner

	//also check if the player1 overlaps with this player. if so do damage to player 1 and put him in his corner
}
