#pragma once
#include "BaseComponent.h"
#include <shared_mutex>

namespace comps
{
	class BoundingBoxComponent;
	class SpriteComponent;
	class PhysicsComponent;
}
namespace comps
{
	class ItemComponent final : public comps::BaseComponent
	{
	public:
		ItemComponent(std::shared_ptr<comps::PhysicsComponent> pPhysicsComp, std::shared_ptr<comps::SpriteComponent> pTextureComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBoxComp, ItemType type);
		~ItemComponent() = default;;

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBoxComp;
		std::shared_ptr<comps::SpriteComponent> m_pSpriteComp;
		std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;

		bool m_HasJumped = false;
		ItemType m_ItemType;
		bool IsLootAble = false;
	};
}