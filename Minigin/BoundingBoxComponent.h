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
		BoundingBoxComponent(float width,float height, std::shared_ptr<comps::PhysicsComponent> pPhysicsComp);
		~BoundingBoxComponent() = default;
		rectangle_ GetBoundingBox(const float elapsedSecs, bool xonly) const;
		void SetAlignment(HAlign hAlign, VAlign vAlign);
		bool IsOverlapping(std::shared_ptr< BoundingBoxComponent> pBoundingBox);


	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:


		std::shared_ptr<PhysicsComponent> m_pPhysicsComp;
		std::pair< HAlign, VAlign> m_Alignment;
		float m_Width;
		float m_Height;


	};
}

