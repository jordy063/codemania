
#pragma once
#include <shared_mutex>
#include <list>
#include "Singleton.h"
#include "structs.h"
class Player;
class Enemy;
class Item;

namespace dae
{
	class Scene;
}
class ItemManager final : dae::Singleton< ItemManager>
{
public:
	void MakeItem(std::shared_ptr<dae::Scene> scene, int level,ItemType type);
	void Update(float elapsedSecs, std::shared_ptr<Player>);

private:
	std::list <std::shared_ptr<Item>> m_pItems;
};
