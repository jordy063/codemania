#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputObserver.h"
#include "InputManager.h"
#include "Singleton.h"

comps::InputComponent::InputComponent(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
	:pPhysicsComp{physicsComp}
	,pSpriteComp{spriteComp}
{
	pInputObserver = std::make_shared<InputObserver>(new InputObserver(this));
	//pInputObserver = new InputObserver(this);
	dae::InputManager::GetInstance().Register(pInputObserver);
	
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

void comps::InputComponent::changeDirection(comps::Direction direction,float speed)
{
	pPhysicsComp->SetMovement(direction,speed);
}
