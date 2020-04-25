#include "MiniginPCH.h"
#include "ItemManager.h"
#include "Item.h"

ItemManager::ItemManager()
{
}
void ItemManager::MakeItem(std::shared_ptr<dae::Scene> scene, int level)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(level);
	//give an item type via parameter and according to the type me make that item
	//also give the position

}
void ItemManager::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);
	//for all enemies update and check if an enemy hits the avatar

	for (std::shared_ptr <Item> item : m_pItems)
	{
		//this will check if an item is taken and if so in ite we'll make a text
		item->Update(elapsedSecs, player);

	}

}
