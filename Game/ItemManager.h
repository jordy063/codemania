#pragma once
#include "Singleton.h"
#include "structs.h"
#include <vector>
#include "Scene.h"
#include <list>
class ItemManager final : public dae::Singleton< ItemManager>
{
public:
	void makeItem(float2 pos, ItemType type,int spriteId);
	void RegisterPlayer(const std::vector<std::shared_ptr<dae::GameObject>>& playerObjects);
	bool CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pItem);
	void DoEffect(ItemType type);
	void RemoveItem(std::shared_ptr<comps::BoundingBoxComponent> pItemBoundingBox);

private:
	//not sure if I need a private vector yet
	std::list< std::shared_ptr<dae::GameObject>> m_pItems;
	std::list<std::shared_ptr<comps::BoundingBoxComponent>> m_pPlayerBoundingBoxes;

	

	
};

