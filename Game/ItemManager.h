#pragma once
#include "Singleton.h"
#include "structs.h"
#include <vector>
#include "Scene.h"
#include <list>
class ItemManager final : public dae::Singleton< ItemManager>
{
public:
	void makeItem(float2 pos, ItemType type);
	void RegisterPlayer(std::shared_ptr<dae::GameObject> playerObject);
	bool CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pItem);
	void DoEffect(ItemType type);
	void RemoveItem(std::shared_ptr<comps::BoundingBoxComponent> pItemBoundingBox);

private:
	//not sure if I need a private vector yet
	std::list< std::shared_ptr<dae::GameObject>> m_pItems;
	std::shared_ptr<comps::BoundingBoxComponent> m_pPlayerBoundingBox;
	

	
};

