#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputObserver.h"
#include "InputManager.h"

comps::InputComponent::InputComponent(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, std::shared_ptr<InputManager> inputManager)
	:pPhysicsComp{physicsComp}
	,pSpriteComp{spriteComp}
	,pInputManager{ inputManager }
{
	pInputObserver = std::make_shared<InputObserver>(new InputObserver(this));
	pInputManager->Register(pInputObserver);

}


comps::InputComponent::~InputComponent()
{
}

void comps::InputComponent::changeDirection(comps::Direction direction)
{
	pPhysicsComp->SetMovement(direction,10);
}
