#include "MiniginPCH.h"
#include "ZenChanAIComponent.h"
#include "BoundingBoxComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"


comps::ZenChanAIComponent::ZenChanAIComponent(std::shared_ptr<dae::GameObject> pPlayerObject, std::shared_ptr<comps::SpriteComponent> pSpriteComp,
	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
	:m_pPhysicsComp(pPhysicsComp)
	,m_pBoundingBoxComp(pBoundingBox)
	,m_pSpriteComp(pSpriteComp)
	, m_SpriteId(1)
	, m_Timer(0)
	, m_ChangeDirectionTime(2)
	, m_JumpTimer(0)
	, m_JumpTime(1.0f)
	,m_pPlayer(pPlayerObject)
{
	m_Speed = { 30.0f,15.0f };
}


void comps::ZenChanAIComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	auto boundingBoxComp = m_pPlayer->GetComponent(ComponentType::BOUNDINGBOXCOMP);
	m_pPlayerBoundingBox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp);

	auto healthComp = m_pPlayer->GetComponent(ComponentType::HEALTHCOMPONENT);
	m_pPlayerHealthComp = std::dynamic_pointer_cast<comps::HealthComponent>(healthComp);

	auto physicsComp = m_pPlayer->GetComponent(ComponentType::PHYSICSCOMP);
	m_pPlayerPhysicsComp = std::dynamic_pointer_cast<comps::PhysicsComponent>(physicsComp);
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

	//If player is on a higher platform and not jumping set DoRandomJumps = true
	//is random is true player will jump around untill he's on the right platform
	
	//need the transform of this gameobject
	
	//float difference{ m_pPhysicsComp->GetTransform()->GetPosition().y - player->GetGameObject()->GetTransform()->GetPosition().y };
	float difference{ m_pPhysicsComp->GetTransform()->GetPosition().y - m_pPlayerBoundingBox->GetBoundingBox(0, 0).posY };
	float playerJumpSpeed{ 60.0f };
	if (difference > playerJumpSpeed&& m_pPlayerPhysicsComp->GetAirBorne() == false)
	{
		DoRandomJumps = true;
	}
	else
	{
		DoRandomJumps = false;
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
			float jumpSpeed{ 250.0f };
			m_MoveUpCommand.Execute(m_pPhysicsComp, m_pSpriteComp, jumpSpeed);
			m_JumpTimer = 0;
			m_JumpTimeSet = false;
		}
		m_JumpTimer += elapsedSecs;
	}
	int randomDirection{ rand() % 2 };


	if (m_Timer > m_ChangeDirectionTime)
	{
		switch (randomDirection)
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
	//if (IsOverlapping(player))
	//{
	//	//do damage and respawn player
	//	player->TakeDamage();
	//}
	if (m_pPlayerBoundingBox->IsOverlapping(m_pBoundingBoxComp))
	{
		//do damage and respawn player
		m_pPlayerHealthComp->DropHealth(1);
	}

	m_Timer += elapsedSecs;
}
