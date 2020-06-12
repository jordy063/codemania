#include "MiniginPCH.h"
#include "MaitaAIComponent.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "BoulderManager.h"
#include "GameInfo.h"
#include "LevelManager.h"
comps::MaitaAIComponent::MaitaAIComponent(std::vector<std::shared_ptr<dae::GameObject>> pPlayerObjects, std::shared_ptr<comps::SpriteComponent> pSpriteComp,
	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox, comps::Direction direction)
	:m_pPhysicsComp(pPhysicsComp)
	, m_pBoundingBoxComp(pBoundingBox)
	, m_pSpriteComp(pSpriteComp)
	, m_SpriteId(1)
	, m_Timer(0)
	, m_ChangeDirectionTime(2)
	, m_JumpTimer(0)
	, m_JumpTime(1.0f)
	, m_pPlayers(pPlayerObjects)
	, m_BoulderTimer()
	, m_BoulderTime(4.0f)
	, m_PreviousSpeed(0)
	, m_IsAnimationStarted(false)
	, m_CurrentDirection(direction)
{
	m_Speed = { 30.0f,15.0f };
}


void comps::MaitaAIComponent::Initialize(const dae::Scene& scene)
{
	//register te components needed during the game
	UNREFERENCED_PARAMETER(scene);
	for (std::shared_ptr<dae::GameObject> pPlayerObject : m_pPlayers)
	{
		auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

		auto healthComp = pPlayerObject->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));

		auto physicsComp = pPlayerObject->GetComponent(ComponentType::PHYSICSCOMP);
		m_pPlayerPhysicsCompss.push_back(std::dynamic_pointer_cast<comps::PhysicsComponent>(physicsComp));
	}
}

void comps::MaitaAIComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);

	//at the start we set the right direction + sprite
	if (m_IsAnimationStarted == false)
	{
		if (m_CurrentDirection == comps::Direction::LEFT)
		{

			m_MoveLeftCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
		}
		else
		{

			m_MoveRightCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
		}

		m_IsAnimationStarted = true;
	}
	DoRandomJumps = false;

	//we check if a player is above the enemy
	for (int i{}; i < m_pPlayerBoundingBoxes.size(); ++i)
	{
		if (m_pPlayerBoundingBoxes[i] != nullptr)
		{
			float difference{ m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBoxes[i]->GetBoundingBox(0, 0).posY - 1 };
			if (difference > 0 && m_pPlayerPhysicsCompss[i]->GetAirBorne() == false)
			{
				DoRandomJumps = true;
			}
		}
	}

	//when DoRandomJumps = true we start a timer and make a jump at a random duration
	if (DoRandomJumps)
	{
		if (m_JumpTimeSet == false)
		{
			int lowBound = int((m_JumpTime - 0.5f) * 100);
			int highBound = int((m_JumpTime + 0.5f) * 100);

			int randomTime{ rand() % (highBound - lowBound) + lowBound };
			m_JumpTimeSet = true;
			m_JumpTime = randomTime * 0.01f;
		}

		if (m_JumpTimer > m_JumpTime)
		{
			//jump
			float jumpSpeed{ 320.0f };
			m_MoveUpCommand.Execute(m_pPhysicsComp, m_pSpriteComp, jumpSpeed);
			m_JumpTimer = 0;
			m_JumpTimeSet = false;
		}
		m_JumpTimer += elapsedSecs;
	}

	//see if the direction should be changed
	if (m_Timer > m_ChangeDirectionTime && DoRandomJumps == true)
	{
		int direction1{};
		int direction2{};
		direction1 = static_cast<int>(m_CurrentDirection);
		direction2 = static_cast<int>(m_CurrentDirection);
		
		//when the enemy goes below the player we update it's direction.
		if (m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBoxes[0]->GetBoundingBox(0, 0).posY >= -0.01f)
		{
			//calculate direction for player 1
			direction1 = CalculatePlayerDirection(m_pPlayers[0]);
		}
		if (m_pPlayerBoundingBoxes.size() == 2)
		{
			if (m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBoxes[1]->GetBoundingBox(0, 0).posY >= -0.01f)
			{
				//calculate direction for player 2
				direction2 = CalculatePlayerDirection(m_pPlayers[1]);
			}
		}
		else
			direction2 = direction1;

		//if the directions are the same we go that way but if not player 1 takes priority
		if (direction1 == direction2 || GameInfo::GetInstance().GetGameMode() == GameMode::SINGLEPLAYER)
		{
			switch (direction1)
			{
			case 0:
				m_MoveRightCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
				m_CurrentDirection = comps::Direction::RIGHT;
				break;
			case 1:
				m_MoveLeftCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
				m_CurrentDirection = comps::Direction::LEFT;
				break;
			}
			m_Timer = 0;
		}

	}

	float2 velocity = m_pPhysicsComp->GetVelocity();

	//if the enemy hits a wall we go the other direction
	if (velocity.x == 0)
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
	
	//when a player overlaps with the enemy we do damage
	for (int i{}; i < m_pPlayerBoundingBoxes.size(); ++i)
	{
		if (m_pPlayerBoundingBoxes[i] != nullptr && m_pPlayerHealthComps[i] != nullptr)
		if (m_pPlayerBoundingBoxes[i]->IsOverlapping(m_pBoundingBoxComp))
		{
			
			if (m_pPlayerHealthComps[i]->GetIsInvinsible() == false)
			{
				m_pPlayerHealthComps[i]->DropHealth(1);
			}

		}
	}
	m_Timer += elapsedSecs;
	m_BoulderTimer += elapsedSecs;

	//we spawn boulder at a fixed duration to the player direction
	if (m_BoulderTimer > m_BoulderTime)
	{
		m_BoulderTimer = 0;
		BoulderManager::GetInstance().MakeBoulder(m_pPhysicsComp->GetTransform()->GetPosition(),m_CurrentDirection);
	}
	LevelManager::GetInstance().UpdateIfBelowLevel(m_pPhysicsComp->GetTransform());
}

//return an int but this corresponds to our comps::direction 
int comps::MaitaAIComponent::CalculatePlayerDirection(std::shared_ptr<dae::GameObject> pPlayer)
{

	if (pPlayer->GetTransform()->GetPosition().x > m_pPhysicsComp->GetTransform()->GetPosition().x)
	{
		return 0;
	}
	else

		return 1;

}
