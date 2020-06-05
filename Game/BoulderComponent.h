#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include "Command.h"

namespace comps
{
	class PhysicsComponent;
}
namespace comps
{
	class BoulderComponent final : public comps::BaseComponent
	{
	public:
		BoulderComponent(std::shared_ptr < comps::PhysicsComponent> pPhysicsComp);
		~BoulderComponent() = default;;
		
	protected:
		virtual void Initialize(const dae::Scene & scene) override;
		virtual void Update(const dae::Scene & scene, float elapsedSecs, float2 pos) override;
	private:
		MoveLeftCommand m_MoveLeftCommand;
		MoveRightCommand m_MoveRightCommand;
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
		comps::Direction m_CurrentDirection;
		float m_Speed;
	};
}
