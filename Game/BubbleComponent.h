#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include "PhysicsComponent.h"

namespace comps
{
	class SpriteComponent;
	class InputComponent;
	class BoundingBoxComponent;
	class HealthComponent;
}
namespace comps
{
	class BubbleComponent final : public comps::BaseComponent
	{
	public:
		BubbleComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp,
			std::shared_ptr<comps::SpriteComponent> pSpriteBoxComp, comps::Direction direction, int id);
		~BubbleComponent() = default;

		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
		std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBoxComp;
		std::shared_ptr<comps::SpriteComponent> m_pSpriteComp;

		float m_BulletSpeed;
		int m_SpriteId;
		comps::Direction m_Direction;
		bool speedSet = false;
		bool m_IsOverlapping = false;
		float m_GoUpTimer;
		float m_GoUpTime;
		bool m_IsTimerReached = false;
		bool m_HasHitEnemy = false;
	};
}

