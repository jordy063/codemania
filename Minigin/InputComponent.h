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

	class InputComponent :public comps::BaseComponent
	{
	public:

		InputComponent(std::shared_ptr<PhysicsComponent> physicsComp, std::shared_ptr<SpriteComponent> spriteComp);
		~InputComponent();

		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

		void changeDirection(Direction direction);
		void StopMoving();

	private:
		std::shared_ptr<PhysicsComponent> pPhysicsComp;
		std::shared_ptr<SpriteComponent> pSpriteComp;
		//InputObserver* pInputObserver;
		std::shared_ptr<InputObserver> pInputObserver;
		std::shared_ptr<dae::InputManager> pInputManager;
		std::map<Direction, int> DirToRow;
		float m_Speed;
	};
}

