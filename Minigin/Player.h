#pragma once
#include "Entity.h"
#include "TileMapLoader.h"


namespace comps
{
	class BoundingBoxComponent;
	class PhysicsComponent;
}
class Player : public Entity
{
public:
	Player(int controllerId, int spriteId, std::shared_ptr<dae::Scene> scene);
	void CreateComponents(int controllerId, int spriteId, std::shared_ptr<dae::Scene> scene);
	void Update(float elapsedSecs);
	rectangle_ GetBoundingBox() const;
	void TakeDamage();
	bool IsAirBorne();
private:
	std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBox;
	std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
	int m_Health;
	float2 screenDeathPosition;
	bool IsInvinsible;

};

