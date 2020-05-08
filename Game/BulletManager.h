#pragma once
#include "Singleton.h"
#include <vector>
#include "structs.h"
#include "PhysicsComponent.h"
#include <list>

namespace comps
{
	class BoundingBoxComponent;
}
class Bullet;
class BulletManager final : public dae::Singleton< BulletManager>
{
public:
	void MakeBullet(const float2& position, comps::Direction direction, int id);
	void RegisterPlayer(std::shared_ptr<dae::GameObject> pPlayerObject);
	void Update();
	void AddBoundingBoxToList(std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);

private:
	std::vector<std::shared_ptr<Bullet>> m_pBullets;
	std::vector<std::shared_ptr<comps::BoundingBoxComponent>> m_pTriggeredBullets;
	std::list<std::shared_ptr<rectangle_>> m_pBulletCollisionList;
	std::shared_ptr<dae::GameObject> m_pPlayerObject;
};

