#pragma once
#include <shared_mutex>
#include <list>
#include "Singleton.h"
#include "structs.h"
#include "PhysicsComponent.h"
class Player;
class Enemy;
class Bullet;

namespace comps
{
	class BoundingBoxComponent;
}


namespace dae 
{
	class Scene;
	class GameObject;
}
class EnemyManager final : public dae::Singleton<EnemyManager>
{
public:
	void MakeEnemies(std::shared_ptr<dae::Scene> scene, int level);
	void Update(float elapsedSecs,std::shared_ptr<Player>);
	int CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBullet, int& index, std::shared_ptr<dae::GameObject>& other);
	void RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers);
	void AddEnemyToList(std::pair<std::shared_ptr<dae::GameObject>, EnemyType> pEnemy);
	void RemoveEnemies();

private:
	std::list <std::pair<std::shared_ptr<dae::GameObject>,int>> m_pEnemies;
	std::vector<std::shared_ptr<dae::GameObject>> m_pPlayerObjects;
	

	void MakeEnemiesLevel0(std::shared_ptr<dae::Scene> scene);
	void MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene);
	void MakeEnemiesLevel2(std::shared_ptr<dae::Scene> scene);
	void MakeEnemy(float2 pos, std::shared_ptr<dae::Scene> scene, EnemyType type, comps::Direction direction);
};

