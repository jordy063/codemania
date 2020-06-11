#include "MiniginPCH.h"
#include "GhostAIComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "LevelManager.h"

//here we'll have to pass the gameobject of the player and get the components. that way we can pass a list of players 
comps::GhostAIComponent::GhostAIComponent(std::vector<std::shared_ptr<dae::GameObject>> pPlayerObjects
	, std::shared_ptr<comps::SpriteComponent> pSpriteComp, std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
	:m_pPhysicsComp(pPhysicsComp)
	,m_pSpriteComp(pSpriteComp)
	,m_pBoundingBoxComp(pBoundingBox)
	, m_IsAnimationStarted(false)
	, m_pPlayers(pPlayerObjects)
{
	m_Speed = { 60.0f,30.0f };

}

void comps::GhostAIComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	for (std::shared_ptr<dae::GameObject> pPlayerObject : m_pPlayers)
	{
		auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

		auto healthComp = pPlayerObject->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));
	}

	
}

void comps::GhostAIComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

	if (m_IsAnimationStarted == false)
	{
		m_pPhysicsComp->SetSpeedX(m_Speed.x);
		m_pPhysicsComp->SetSpeedY(m_Speed.y);
		m_MoveRightCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
		m_IsAnimationStarted = true;
	}

	float2 testVelocity = m_pPhysicsComp->GetVelocity();

	if (testVelocity.x == 0)
	{
		if (m_CurrentDirection == comps::Direction::RIGHT)
		{
			m_MoveLeftCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
			m_CurrentDirection = comps::Direction::LEFT;
		}
		else if (m_CurrentDirection == comps::Direction::LEFT)
		{
			m_MoveRightCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
			m_CurrentDirection = comps::Direction::RIGHT;
		}
	}
	if (testVelocity.y == 0)
	{
		if (m_PreviousSpeed > 0)
		{
			m_pPhysicsComp->SetSpeedY(-m_Speed.y);
		}
		else if (m_PreviousSpeed < 0)
		{
			m_pPhysicsComp->SetSpeedY(m_Speed.y);
		}
	}

	//put function in boundingbox isOverlapping
	for (int i{}; i < m_pPlayerHealthComps.size(); ++i)
	{
		if(m_pPlayerBoundingBoxes[i] != nullptr && m_pPlayerHealthComps[i] != nullptr)
		if (m_pPlayerBoundingBoxes[i]->IsOverlapping(m_pBoundingBoxComp))
		{
			//do damage and respawn player
			
			if (m_pPlayerHealthComps[i]->GetInvinsible() == false)
			{
				m_pPlayerHealthComps[i]->DropHealth(1);
			}
			
		}
	}
	m_PreviousSpeed = testVelocity.y;


	//check if leaving the current level
	LevelManager::GetInstance().UpdateIfAboveLevel(m_pPhysicsComp->GetTransform());
	LevelManager::GetInstance().UpdateIfBelowLevel(m_pPhysicsComp->GetTransform());
}
