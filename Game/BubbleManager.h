#pragma once
#include "Singleton.h"
#include <vector>
#include "structs.h"
#include "PhysicsComponent.h"
#include <list>

enum HitType
{
	NOHIT,
	UPHIT,
	SIDEHIT
};

namespace comps
{
	class BoundingBoxComponent;
	class CollisionComponent;
	class PhysicsComponent;
}
class Bullet;
class BubbleManager final : public dae::Singleton< BubbleManager>
{
public:
	void MakeBullet(const float2& position, comps::Direction direction, int id);
	void RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers);
	void Update();
	void AddBoundingBoxToList(std::shared_ptr<comps::CollisionComponent> pCollisionComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);
	void RemoveBullet(std::shared_ptr<comps::CollisionComponent> pCollisionComp,std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox);
	HitType CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox, int playerId);
	bool CheckPlayer2HitsBullet();
	float2 GetBubbleSpeed() const { return m_BulletSpeed; }
	void MovePlayerWithBullet(int playerId);

private:
	std::list<std::shared_ptr<comps::BoundingBoxComponent>> m_pTriggeredBullets;
	std::list<std::shared_ptr<dae::GameObject>> m_pBullets;
	std::vector<std::shared_ptr<comps::BoundingBoxComponent>> m_pPlayerBoundingBoxes;
	std::vector < std::shared_ptr<comps::PhysicsComponent>> m_pPlayerPhysicsComps;
	float2 m_BulletSpeed = { 60.f ,15.0f};
};

