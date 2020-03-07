#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputObserver.h"
#include "InputManager.h"
#include "Singleton.h"

comps::InputComponent::InputComponent(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
	:pPhysicsComp{physicsComp}
	,pSpriteComp{spriteComp}
	, m_Speed{30.0f}
{
	DirToRow[Direction::LEFT] = 3;
	DirToRow[Direction::RIGHT] = 1;
	DirToRow[Direction::UP] = 2;
	DirToRow[Direction::DOWN] = 0;


	pInputObserver = std::make_shared<InputObserver>(this);
	//pInputObserver = new InputObserver(this);
	dae::InputManager::GetInstance().Register(pInputObserver);
	pSpriteComp->SetActiveRowStop();
}


comps::InputComponent::~InputComponent()
{
}

void comps::InputComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::InputComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

}

void comps::InputComponent::changeDirection(Direction direction)
{
	
	switch (direction)
	{
		case Direction::LEFT:
		{
		
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp);
		}
		break;

		case Direction::RIGHT:
		{
			
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp);
		}
		break;

		case Direction::UP:
		{
			
			m_MoveUpCommand.Execute(pPhysicsComp, pSpriteComp);
		}
		break;

		case Direction::DOWN:
		{
			
			m_MoveDownCommand.Execute(pPhysicsComp, pSpriteComp);
		}
		break;
	}
}

void comps::InputComponent::StopMoving()
{
	
	m_StopMovingCommand.Execute(pPhysicsComp, pSpriteComp);
}

