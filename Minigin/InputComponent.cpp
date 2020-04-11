#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputObserver.h"
#include "InputManager.h"
#include "Singleton.h"

comps::InputComponent::InputComponent(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,int controllerId)
	:pPhysicsComp{physicsComp}
	,pSpriteComp{spriteComp}
	, m_timeout{0}
{
	DirToRow[Direction::LEFT] = 3;
	DirToRow[Direction::RIGHT] = 1;
	DirToRow[Direction::UP] = 2;
	DirToRow[Direction::DOWN] = 0;


	pInputObserver = std::make_shared<InputObserver>(this, controllerId);
	//pInputObserver = new InputObserver(this);
	dae::InputManager::GetInstance().Register(pInputObserver,controllerId);
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
	m_timeout -= elapsedSecs;
}

void comps::InputComponent::changeDirection(Direction direction)
{
	float movementSpeed{ pPhysicsComp->GetMovementSpeed() };
	float jumpSpeed{ 180 };
	
	switch (direction)
	{
		case Direction::LEFT:
		{
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
		}
		break;

		case Direction::RIGHT:
		{
			
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
		}
		break;

		case Direction::UP:
		{
			
			m_MoveUpCommand.Execute(pPhysicsComp, pSpriteComp, jumpSpeed);
		}
		break;

		case Direction::DOWN:
		{
			
			m_MoveDownCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
		}
		break;
	}
}
void comps::InputComponent::ShootBullet(Direction direction)
{
	float movementSpeed{ 200 };


	if (m_timeout > 0)
		return;
	m_timeout = 2;
	switch (direction)
	{
	case Direction::LEFT:
	{
		m_ShootLeftCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
	}
	break;

	case Direction::RIGHT:
	{

		m_ShootRightCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
	}
	break;

	case Direction::UP:
	{

		m_ShootUpCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
	}
	break;

	case Direction::DOWN:
	{

		m_ShootDownCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed);
	}
	break;
	}
}

void comps::InputComponent::StopMoving()
{
	
	m_StopMovingCommand.Execute(pPhysicsComp, pSpriteComp,0);
}

