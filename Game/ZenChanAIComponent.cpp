#include "MiniginPCH.h"
#include "ZenChanAIComponent.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "Menu.h"
#include "LevelManager.h"


comps::ZenChanAIComponent::ZenChanAIComponent(std::vector<std::shared_ptr<dae::GameObject>> pPlayerObjects, std::shared_ptr<comps::SpriteComponent> pSpriteComp,
	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
	:m_pPhysicsComp(pPhysicsComp)
	,m_pBoundingBoxComp(pBoundingBox)
	,m_pSpriteComp(pSpriteComp)
	, m_SpriteId(1)
	, m_ChangeDirectionTime(2)
	, m_JumpTimer(0)
	, m_JumpTime(1.0f)
	,m_pPlayers(pPlayerObjects)
	, m_CurrentDirection(comps::Direction::RIGHT)
	,m_IsAnimationStarted(false)
	,m_PreviousSpeed(0)
	, m_StartTime(5)
	,m_StartTimer(0)
{
	m_Speed = { 30.0f,15.0f };
}


void comps::ZenChanAIComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	for (std::shared_ptr<dae::GameObject> pPlayerObject : m_pPlayers)
	{
		auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

		auto healthComp = pPlayerObject->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_pPlayerHealthComps.push_back( std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));

		auto physicsComp = pPlayerObject->GetComponent(ComponentType::PHYSICSCOMP);
		m_pPlayerPhysicsCompss.push_back( std::dynamic_pointer_cast<comps::PhysicsComponent>(physicsComp));
	}
}

void comps::ZenChanAIComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);
	if (m_IsAnimationStarted == false)
	{
		m_MoveRightCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
		m_IsAnimationStarted = true;
	}
	DoRandomJumps = false;
	for (int i{}; i < m_pPlayerBoundingBoxes.size(); ++i)
	{
		float difference{ m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBoxes[i]->GetBoundingBox(0, 0).posY - 1 };
		if (difference > 0 && m_pPlayerPhysicsCompss[i]->GetAirBorne() == false)
		{
			DoRandomJumps = true;
		}
		
	}
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


	if (m_Timer > m_ChangeDirectionTime && DoRandomJumps == true)
	{
		int direction1{};
		int direction2{};
		direction1 = static_cast<int>(m_CurrentDirection);
		direction2 = static_cast<int>(m_CurrentDirection);
		if (m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBoxes[0]->GetBoundingBox(0, 0).posY > -0.01f)
		{
			//calculate direction for player 1
			direction1 = CalculatePlayerDirection(m_pPlayers[0]);
		}
		if (m_pPlayerBoundingBoxes[1] != nullptr)
		{
			if (m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBoxes[1]->GetBoundingBox(0, 0).posY >= -0.01f)
			{
				//calculate direction for player 2
				direction2 = CalculatePlayerDirection(m_pPlayers[1]);
			}
		}
		else
			direction2 = direction1;
		if (direction1 == direction2 ||Menu::GetInstance().GetGameMode()==GameMode::SINGLEPLAYER)
		{
			switch (direction1)
			{
			case 0:
				m_MoveRightCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
				break;
			case 1:
				m_MoveLeftCommand.Execute(m_pPhysicsComp, m_pSpriteComp, m_Speed.x);
				break;
			}
			m_Timer = 0;
		}
		
	}

	float2 velocity = m_pPhysicsComp->GetVelocity();

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
	//if (IsOverlapping(player))
	//{
	//	//do damage and respawn player
	//	player->TakeDamage();
	//}
	for (int i{}; i < m_pPlayerBoundingBoxes.size(); ++i)
	{
		
		if (m_pPlayerBoundingBoxes[i]->IsOverlapping(m_pBoundingBoxComp))
		{
			//do damage and respawn player
		
			if (m_pPlayerHealthComps[i]->GetInvinsible() == false)
			{
				m_pPlayerHealthComps[i]->DropHealth(1);
				LevelManager::GetInstance().ResetPlayerPos(i);
			}
			
				
			
		}
	}
	/*m_StartTimer += elapsedSecs;
	if (m_StartTimer < m_StartTime)
		LevelManager::GetInstance().UpdateIfBelowLevel(m_pPhysicsComp->GetTransform(), true, m_StartPos);
	else*/
		LevelManager::GetInstance().UpdateIfBelowLevel(m_pPhysicsComp->GetTransform());
}

int comps::ZenChanAIComponent::CalculatePlayerDirection(std::shared_ptr<dae::GameObject> pPlayer)
{
	
	if (pPlayer->GetTransform()->GetPosition().x > m_pPhysicsComp->GetTransform()->GetPosition().x)
	{
		return 0;
	}
	else
	
		return 1;
		
}
