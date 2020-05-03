#pragma once
#include "Singleton.h"
#include <vector>
#include "structs.h"
#include "PhysicsComponent.h"


class Bullet;
class BulletManager final : public dae::Singleton< BulletManager>
{
public:
	void MakeBullet(const float2& position, comps::Direction direction, float speed, int id);
	void Update();

private:
	std::vector<std::shared_ptr<Bullet>> m_pBullets;
};

