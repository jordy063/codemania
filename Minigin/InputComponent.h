#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

namespace dae
{
	class InputManager;
}
class InputObserver;

namespace comps
{

	class InputComponent : comps::BaseComponent
	{
	public:

		InputComponent(std::shared_ptr<PhysicsComponent> physicsComp, std::shared_ptr<SpriteComponent> spriteComp,std::shared_ptr<InputManager> inputManager);
		~InputComponent();

		void changeDirection(Direction direction);

	private:
		std::shared_ptr<PhysicsComponent> pPhysicsComp;
		std::shared_ptr<SpriteComponent> pSpriteComp;
		std::shared_ptr<InputObserver> pInputObserver;
		std::shared_ptr<dae::InputManager> pInputManager;
	};
}

