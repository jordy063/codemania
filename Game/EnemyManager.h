#pragma once
#include <shared_mutex>
#include <list>
#include "Singleton.h"
class Player;
class Enemy;
class Bullet;

namespace dae 
{
	class Scene;
}
class EnemyManager final : public dae::Singleton<EnemyManager>
{
public:
	void MakeEnemies(std::shared_ptr<dae::Scene> scene, int level);
	void Update(float elapsedSecs,std::shared_ptr<Player>);
	bool CheckIfHit(std::shared_ptr<Bullet> pBullet);

private:
	std::list <std::shared_ptr<Enemy>> m_pEnemies;

	void MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene);
};

