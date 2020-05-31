#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputObserver.h"
#include "InputManager.h"
#include "Singleton.h"

comps::InputComponent::InputComponent(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,int controllerId)
	:pPhysicsComp{physicsComp}
	,pSpriteComp{spriteComp}
	, m_timeout1{0}
	,m_timeout2{0}
	, m_ShootDuration{1.0}
{
	DirToRow[Direction::LEFT] = 0 ;
	DirToRow[Direction::RIGHT] = 1;
	UNREFERENCED_PARAMETER(controllerId);
	//pInputObserver = std::make_shared<InputObserver>(this, controllerId);
	////pInputObserver = new InputObserver(this);
	//dae::InputManager::GetInstance().Register(pInputObserver,controllerId);
	//pSpriteComp->SetActiveRowStop();

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
	m_timeout1 -= elapsedSecs;
	m_timeout2 -= elapsedSecs;


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
	float jumpSpeed{ 320 };
	
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
void comps::InputComponent::ShootBullet(Direction direction,int spriteId)
{
	float movementSpeed{ 20 };
	
	//set timer
	switch (spriteId)
	{
	case 0:
		if (m_timeout1 > 0)
			return;

		m_timeout1 = 2;
		break;
	case 1:
		if (m_timeout2 > 0)
			return;

		m_timeout2 = 2;
		break;
	}

	//shoot bullet in the right direction
	switch (direction)
	{
	case Direction::LEFT:
	{
		m_IsShooting = true;
		m_ShootLeftCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed,spriteId);
		m_ActiveRow = 1;
	}
	break;

	case Direction::RIGHT:
	{
		m_IsShooting = true;
		m_ShootRightCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, spriteId);
		m_ActiveRow = 0;
	}
	break;

	case Direction::UP:
	{

		m_ShootUpCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, spriteId);
	}
	break;

	case Direction::DOWN:
	{

		m_ShootDownCommand.Execute(pPhysicsComp, pSpriteComp, movementSpeed, spriteId);
	}
	break;
	}
}

void comps::InputComponent::MakeObserver(int controllerId)
{
	pInputObserver = std::make_shared<InputObserver>(this, controllerId);
	//pInputObserver = new InputObserver(this);
	dae::InputManager::GetInstance().Register(pInputObserver, controllerId);
}

void comps::InputComponent::StopMoving()
{
	
	m_StopMovingCommand.Execute(pPhysicsComp, pSpriteComp,0);
}

