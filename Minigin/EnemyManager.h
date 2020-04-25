#pragma once
#include <shared_mutex>
#include <list>
class Player;
class Enemy;

namespace dae
{
	class Scene;
}
class EnemyManager
{
public:
	EnemyManager();
	void MakeEnemies(std::shared_ptr<dae::Scene> scene, int level);
	void Update(float elapsedSecs,std::shared_ptr<Player>);

private:
	std::list <std::shared_ptr<Enemy>> m_pEnemies;

	void MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene);
};

