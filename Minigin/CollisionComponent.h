#pragma once
#include "BaseComponent.h"
#include <list>
#include "PhysicsComponent.h"
#include <shared_mutex>

namespace comps
{
	class BoundingBoxComponent;
}

namespace comps
{
	class CollisionComponent final : public comps::BaseComponent
	{
	public:
		CollisionComponent(std::list < std::shared_ptr<rectangle_>> collisionWalls, std::list < std::shared_ptr<rectangle_>> collisionPlatforms,
			std::shared_ptr<PhysicsComponent> physicsComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);
		~CollisionComponent() = default;
		void SetExtraCollisions(std::list<std::shared_ptr<comps::BoundingBoxComponent>> extraCollisionList);
		void SetCollision(std::list < std::shared_ptr<rectangle_>> collisionWalls, std::list < std::shared_ptr<rectangle_>> collisionPlatforms);
		void SetActive(bool isActive);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:


		std::list < std::shared_ptr<rectangle_>> m_CollisionWalls;
		std::list < std::shared_ptr<rectangle_>> m_CollisionPlatforms;
		std::list < std::shared_ptr<comps::BoundingBoxComponent>> m_ExtraCollisions;
		std::shared_ptr<PhysicsComponent> m_pPhysicsComp;
		std::shared_ptr<BoundingBoxComponent> m_pBoundingBoxComp;
		std::pair< HAlign, VAlign> m_Alignment;
		

		bool IsRectangleOverlapping(float elapsedSecs, bool xonly, std::list < std::shared_ptr<rectangle_>>& collision) const;
		void GetCollisionList();
		std::list < std::shared_ptr<rectangle_>> m_CollisionList;
		bool m_IsActive = true;
	};
}

