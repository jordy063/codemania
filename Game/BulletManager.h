#pragma once
#include "Singleton.h"
#include <vector>
#include "structs.h"
#include "PhysicsComponent.h"
#include <list>

namespace comps
{
	class BoundingBoxComponent;
	class CollisionComponent;
}
class Bullet;
class BulletManager final : public dae::Singleton< BulletManager>
{
public:
	void MakeBullet(const float2& position, comps::Direction direction, int id);
	void RegisterPlayer(std::shared_ptr<dae::GameObject> pPlayerObject);
	void Update();
	void AddBoundingBoxToList(std::shared_ptr<comps::CollisionComponent> pCollisionComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);
	void RemoveBullet(std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);
	bool CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox);

private:
	std::list<std::shared_ptr<comps::BoundingBoxComponent>> m_pTriggeredBullets;
	std::list<std::shared_ptr<dae::GameObject>> m_pBullets;
	std::shared_ptr<comps::BoundingBoxComponent> m_pPlayerBoundingBox;
};

