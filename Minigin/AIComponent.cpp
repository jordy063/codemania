#include "MiniginPCH.h"
#include "AIComponent.h"

int comps::AIComponent::m_Seed = 0;
comps::AIComponent::AIComponent(std::shared_ptr<PhysicsComponent> physicsComp, std::shared_ptr<SpriteComponent> spriteComp)
	:pPhysicsComp{ physicsComp }
	, pSpriteComp{ spriteComp }
	, m_Speed{ 30.0f }
	, m_ChangeDirectionTime{ 1 }
	, m_Timer{}
{
	std::srand(m_Seed);
	++m_Seed;
	DirToRow[Direction::LEFT] = 3;
	DirToRow[Direction::RIGHT] = 1;
	DirToRow[Direction::UP] = 2;
	//DirToRow[Direction::DOWN] = 0;
	
	pSpriteComp->SetActiveRowStop();

}

comps::AIComponent::~AIComponent()
{
	
}

void comps::AIComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::AIComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

	//add logic for ai

	int randomDirection{ rand() % 4 };
	float jumpSpeed{ 180.0f };

	if (m_Timer > m_ChangeDirectionTime)
	{
		switch (randomDirection)
		{
		case 0:
			
			break;
		case 1:
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed);
			break;
		case 2:
			m_MoveUpCommand.Execute(pPhysicsComp, pSpriteComp, jumpSpeed);
			break;
		case 3:
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp, m_Speed);
			break;
		}
		m_Timer = 0;
	}
	m_Timer += elapsedSecs;
	
}
