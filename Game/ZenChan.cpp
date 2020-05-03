#include "MiniginPCH.h"
#include "ZenChan.h"
#include "Player.h"

ZenChan::ZenChan(std::shared_ptr<dae::Scene> scene, int level)
	:Enemy(scene, level, 0, true)
	, m_SpriteId(1)
	, m_Timer(0)
	, m_ChangeDirectionTime(2)
	, m_JumpTimer(0)
	, m_JumpTime(1.0f)
{
	m_Speed = { 30.0f,15.0f };
}

void ZenChan::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	if (AnimationStarted == false)
	{
		m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x);
		AnimationStarted = true;
	}

	//If player is on a higher platform and not jumping set DoRandomJumps = true
	//is random is true player will jump around untill he's on the right platform

	float difference{ m_EntityObject->GetTransform()->GetPosition().y - player->GetGameObject()->GetTransform()->GetPosition().y };
	float playerJumpSpeed{ 60.0f };
	if (difference > playerJumpSpeed&& player->IsAirBorne() == false)
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
			m_JumpTime = randomTime *0.01f;
		}

		if (m_JumpTimer > m_JumpTime)
		{
			//jump
			float jumpSpeed{ 180.0f };
			m_MoveUpCommand.Execute(pPhysicsComp, pSpriteComp, jumpSpeed);
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
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x);
			break;
		case 1:
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x);
			break;
		}
		m_Timer = 0;
	}

	float2 testVelocity = pPhysicsComp->GetVelocity();

	if (testVelocity.x == 0)
	{
		if (m_CurrentDirection == comps::Direction::RIGHT)
		{
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x);
			m_CurrentDirection = comps::Direction::LEFT;
		}
		else if (m_CurrentDirection == comps::Direction::LEFT)
		{
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x);
			m_CurrentDirection = comps::Direction::RIGHT;
		}
	}
	if (IsOverlapping(player))
	{
		//do damage and respawn player
		player->TakeDamage();
	}

	m_Timer += elapsedSecs;

}

void ZenChan::SetIsHit()
{
	
}
