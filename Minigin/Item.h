#pragma once
#include "structs.h"
#include "Scene.h"

namespace comps
{
	class BoundingBoxComponent;
	class PhysicsComponent;
	class SpriteComponent;
}

class Item : public Entity
{
public:
	Item(std::shared_ptr<dae::Scene> scene, int level, int id);
	virtual void CreateComponents(std::shared_ptr<dae::Scene> scene, int level,int id);
	virtual void Update(float elapsedSecs, std::shared_ptr<Player> player) override;

protected:
	std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBox;
	bool IsOverlapping(std::shared_ptr<Player> player);
	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp;
	std::shared_ptr<comps::SpriteComponent> pSpriteComp;

};

