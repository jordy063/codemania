#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include "Command.h"

namespace comps
{
	class PhysicsComponent;
	class HealthComponent;
	class BoundingBoxComponent;
}
namespace comps
{
	class BoulderComponent final : public comps::BaseComponent
	{
	public:
		BoulderComponent(std::shared_ptr < comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox,
			std::vector<std::shared_ptr<comps::HealthComponent>> pPlayerHealthComps);
		~BoulderComponent() = default;;
		
	protected:
		virtual void Initialize(const dae::Scene & scene) override;
		virtual void Update(const dae::Scene & scene, float elapsedSecs, float2 pos) override;
	private:
		MoveLeftCommand m_MoveLeftCommand;
		MoveRightCommand m_MoveRightCommand;
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
		std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBox;
		comps::Direction m_CurrentDirection;
		std::vector<std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;
		float m_Speed;
	};
}
