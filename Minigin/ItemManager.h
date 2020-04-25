
#pragma once
#include <shared_mutex>
#include <list>
class Player;
class Enemy;
class Item;

namespace dae
{
	class Scene;
}
class ItemManager
{
public:
	ItemManager();
	void MakeItem(std::shared_ptr<dae::Scene> scene, int level);
	void Update(float elapsedSecs, std::shared_ptr<Player>);

private:
	std::list <std::shared_ptr<Item>> m_pItems;
};
