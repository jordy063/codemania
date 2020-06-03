
#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include "Command.h"
namespace comps
{
	class PhysicsComponent;
	class SpriteComponent;
	class InputComponent;
	class BoundingBoxComponent;
	class HealthComponent;
}
namespace comps
{
	class ZenChanAIComponent final : public comps::BaseComponent
	{
	public:
		ZenChanAIComponent(std::vector<std::shared_ptr<dae::GameObject>> pPlayerObjects
			,std::shared_ptr<comps::SpriteComponent> pSpriteComp, std::shared_ptr<comps::PhysicsComponent> pPhysicsComp,
			std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		std::vector<std::shared_ptr<comps::BoundingBoxComponent>> m_pPlayerBoundingBoxes;
		std::vector<std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
		std::shared_ptr<comps::SpriteComponent> m_pSpriteComp;
		std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBoxComp;
		std::vector<std::shared_ptr<comps::PhysicsComponent>> m_pPlayerPhysicsCompss;
		bool m_IsAnimationStarted;
		float2 m_Speed;

		//commands
		MoveLeftCommand m_MoveLeftCommand;
		MoveRightCommand m_MoveRightCommand;
		MoveUpCommand m_MoveUpCommand;
		MoveDownCommand m_MoveDownCommand;

		comps::Direction m_CurrentDirection;
		float m_PreviousSpeed;

		float m_Timer;
		float m_ChangeDirectionTime;
		int m_SpriteId;
		float m_JumpTimer;
		float m_JumpTime;
		bool m_JumpTimeSet = false;
		bool DoRandomJumps = false;
		std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;

		int CalculatePlayerDirection(std::shared_ptr<dae::GameObject> pPlayer);
	};
}