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
	class GhostAIComponent final : public comps::BaseComponent
	{
	public:
		GhostAIComponent(std::vector<std::shared_ptr<dae::GameObject>> pPlayerObjects
			, std::shared_ptr<comps::SpriteComponent> pSpriteComp, std::shared_ptr<comps::PhysicsComponent> pPhysicsComp,
			std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox, comps::Direction direction);
		~GhostAIComponent() = default;;
	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		std::vector<std::shared_ptr<comps::BoundingBoxComponent>> m_pPlayerBoundingBoxes;
		std::vector<std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
		std::shared_ptr<comps::SpriteComponent> m_pSpriteComp;
		std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBoxComp;

		bool m_IsAnimationStarted;
		float2 m_Speed;

		//commands
		MoveLeftCommand m_MoveLeftCommand;
		MoveRightCommand m_MoveRightCommand;
		MoveUpCommand m_MoveUpCommand;
		MoveDownCommand m_MoveDownCommand;

		comps::Direction m_CurrentDirection;
		float m_PreviousSpeed;
		std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
	};
}
