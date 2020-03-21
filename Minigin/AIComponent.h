#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "Command.h"

namespace comps
{
	class AIComponent : public comps::BaseComponent
	{
	public:
		AIComponent(std::shared_ptr<PhysicsComponent> physicsComp, std::shared_ptr<SpriteComponent> spriteComp);
		~AIComponent();

		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;


	private:
		std::shared_ptr<PhysicsComponent> pPhysicsComp;
		std::shared_ptr<SpriteComponent> pSpriteComp;

		std::map<Direction, int> DirToRow;
		float m_Speed;

		//commands
		MoveLeftCommand m_MoveLeftCommand;
		MoveRightCommand m_MoveRightCommand;
		MoveUpCommand m_MoveUpCommand;
		MoveDownCommand m_MoveDownCommand;
		StopMovingCommand m_StopMovingCommand;

		static int m_Seed;
		float m_Timer;
		float m_ChangeDirectionTime;
	};
}


