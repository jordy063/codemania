#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputObserver.h"
#include "InputManager.h"
#include "Singleton.h"

comps::InputComponent::InputComponent(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,int controllerId)
	:pPhysicsComp{physicsComp}
	,pSpriteComp{spriteComp}
	, m_timeout{0}
	, m_ShootDuration{1.0}
	, m_SpriteId(controllerId+1)
{
	DirToRow[Direction::LEFT] = 0 ;
	DirToRow[Direction::RIGHT] = 1;

	pInputObserver = std::make_shared<InputObserver>(this, controllerId);
	//pInputObserver = new InputObserver(this);
	dae::InputManager::GetInstance().Register(pInputObserver,controllerId);
	pSpriteComp->SetActiveRowStop();

	if (m_SpriteId == -1)
	{
		m_SpriteId = 1;
	}
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


	if (m_IsShooting)
	{
		m_ShootTimer += elapsedSecs;

		if (m_ShootTimer > m_ShootDuration)
		{
			pSpriteComp->SetActiveRow(m_ActiveRow);
			pSpriteComp->SetActiveRowStop();
			m_ShootTimer = 0;
			m_IsShooting = false;
		}
	}
}

void comps::InputComponent::changeDirection(Direction direction)
{
	float movementSpeed{ pPhysicsComp->GetMovementSpeed() };
	float jumpSpeed{ 180 };
	
	switch (direction)
	{
		case Direction::LEFT:
		{
			m_MoveLeftCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
		}
		break;

		case Direction::RIGHT:
		{
			
			m_MoveRightCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
		}
		break;

		case Direction::UP:
		{
			
			m_MoveUpCommand.Execute(pPhysicsComp, pSpriteComp, jumpSpeed, m_SpriteId);
		}
		break;

		case Direction::DOWN:
		{
			
			m_MoveDownCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
		}
		break;
	}
}
void comps::InputComponent::ShootBullet(Direction direction)
{
	float movementSpeed{ 20 };


	if (m_timeout > 0)
		return;
	m_timeout = 2;
	switch (direction)
	{
	case Direction::LEFT:
	{
		m_IsShooting = true;
		m_ShootLeftCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
		m_ActiveRow = 1 + 2* m_SpriteId;
	}
	break;

	case Direction::RIGHT:
	{
		m_IsShooting = true;
		m_ShootRightCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
		m_ActiveRow = 0 + 2* m_SpriteId;
	}
	break;

	case Direction::UP:
	{

		m_ShootUpCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
	}
	break;

	case Direction::DOWN:
	{

		m_ShootDownCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, m_SpriteId);
	}
	break;
	}
}

void comps::InputComponent::StopMoving()
{
	
	m_StopMovingCommand.Execute(pPhysicsComp, pSpriteComp,0, m_SpriteId);
}

