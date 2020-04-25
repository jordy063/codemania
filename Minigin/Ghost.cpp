#include "MiniginPCH.h"
#include "Ghost.h"
#include "Player.h"
#include "BoundingBoxComponent.h"

Ghost::Ghost(std::shared_ptr<dae::Scene> scene,int level)
	:Enemy(scene,level,1,false)
	,m_SpriteId(1)
{
	m_Speed = { 30.0f,15.0f };
}

void Ghost::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);
	if (AnimationStarted == false)
	{
		pPhysicsComp->SetSpeedX(m_Speed.x);
		pPhysicsComp->SetSpeedY(m_Speed.y);
		m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x, m_SpriteId);
		AnimationStarted = true;
	}

	float2 testVelocity = pPhysicsComp->GetVelocity();

	if (testVelocity.x == 0)
	{
		if (m_CurrentDirection == comps::Direction::RIGHT)
		{
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x, m_SpriteId);
			m_CurrentDirection = comps::Direction::LEFT;
		}
		else if (m_CurrentDirection == comps::Direction::LEFT)
		{
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed.x, m_SpriteId);
			m_CurrentDirection = comps::Direction::RIGHT;
		}
	}
	if (testVelocity.y == 0)
	{
		if (m_PreviousSpeed > 0)
		{
			pPhysicsComp->SetSpeedY(-m_Speed.y);
		}
		else if (m_PreviousSpeed < 0)
		{
			pPhysicsComp->SetSpeedY(m_Speed.y);
		}
	}

	if (IsOverlapping(player))
	{
		//do damage and respawn player
		player->TakeDamage();
	}
	m_PreviousSpeed = testVelocity.y;


	//just changes direction whenever a wal or platform is hit.
	//a bit like a bouncing ball

}
