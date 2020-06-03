#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include "structs.h"
namespace comps
{
	class TextureComponent;
	class PhysicsComponent;
}
namespace comps
{
	class ScorePopUpComponent final : public comps::BaseComponent
	{
	public:
		ScorePopUpComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, ItemType itemType);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
		float2 m_OriginalPosition;
		float m_TravelDistance;
		ItemType m_ItemType;
	};
}

