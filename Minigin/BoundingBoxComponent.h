#pragma once
#include "structs.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include <list>
#include "PhysicsComponent.h"
#include "TextureComponent.h"

//has to be a component I think?
namespace comps
{
	class BoundingBoxComponent final : public comps::BaseComponent
	{
	public:
		BoundingBoxComponent(std::list < std::shared_ptr<rectangle_>> collisionWalls, std::list < std::shared_ptr<rectangle_>> collisionPlatforms, std::shared_ptr<PhysicsComponent> physicsComp,float width,float height);
		rectangle_ GetBoundingBox(const float elapsedSecs, bool xonly) const;
		void SetAlignment(HAlign hAlign, VAlign vAlign);
		void SetNewBoundingBox(std::list < std::shared_ptr<rectangle_>> collisionWalls, std::list < std::shared_ptr<rectangle_>> collisionPlatforms);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:


		std::list < std::shared_ptr<rectangle_>> m_CollisionWalls;
		std::list < std::shared_ptr<rectangle_>> m_CollisionPlatforms;
		std::shared_ptr<PhysicsComponent> m_pPhysicsComp;
		std::pair< HAlign, VAlign> m_Alignment;
		float m_Width;
		float m_Height;

		bool IsRectangleOverlapping(float elapsedSecs, bool xonly, std::list < std::shared_ptr<rectangle_>>& collision);


	};
}

