#include "MiniginPCH.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "BoundingBoxComponent.h"
#include "CollisionComponent.h"
#include "Scene.h"
#include "TileMapLoader.h"
#include "ItemComponent.h"
#include "SceneManager.h"

void ItemManager::makeItem(float2 pos,ItemType type,int spriteId)
{
	UNREFERENCED_PARAMETER(pos);
	//add all necesary components to a gameobject

	auto itemObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	//add this to scene
	dae::SceneManager::GetInstance().GetActiveScene()->Add(itemObject);
	itemObject->GetTransform()->Translate(pos);
	//needs a texture/physics/collision/itemComp
	
	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/ItemSheet.png", 4,4, 0, 0.2f, 22, 22));
	auto pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(itemObject->GetTransform(), true));

	auto pBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22, pPhysicsComp));
	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), pPhysicsComp, pBoundingBoxComp));
	auto pItemComponent = std::shared_ptr<comps::ItemComponent>(new comps::ItemComponent(pPhysicsComp,pSpriteComp,pBoundingBoxComp, type, spriteId));


	itemObject->AddComponent(pSpriteComp,ComponentType::SPRITECOMP);
	itemObject->AddComponent(pBoundingBoxComp, ComponentType::BOUNDINGBOXCOMP);
	itemObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	itemObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	itemObject->AddComponent(pItemComponent, ComponentType::ITEMCOMPONENT);

	m_pItems.push_back(itemObject);

	//question
	//when it hits a platform it goes ignore that platform the first time but set xSpeed = 0;
	//aside from that everything is the same as the normal collisionComp
	//could make a function that tells me if I hit a wall

}

void ItemManager::RegisterPlayer(const std::vector<std::shared_ptr<dae::GameObject>>& playerObjects)
{
	for (std::shared_ptr<dae::GameObject> pPlayer : playerObjects)
	{
		auto boundingBoxComp = pPlayer->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		auto pPlayerBoundingBox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp);
		m_pPlayerBoundingBoxes.push_back(pPlayerBoundingBox);
	}

	
}

bool ItemManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pItemBoundingBox)
{
	for (std::shared_ptr<comps::BoundingBoxComponent> pPlayerBoundingBox : m_pPlayerBoundingBoxes)
	{
		if (pPlayerBoundingBox->IsOverlapping(pItemBoundingBox))
		{
			return true;

		}
	}
	return false;
}

void ItemManager::DoEffect(ItemType type)
{
	switch (type)
	{
	case FRIES:
		break;
	case MELON:
		break;
	default:
		break;
	}

}

void ItemManager::RemoveItem(std::shared_ptr<comps::BoundingBoxComponent> pItemBoundingBox)
{
	std::shared_ptr<dae::GameObject> pGameObjectToRemove{ nullptr };
	for (std::shared_ptr<dae::GameObject> pGameobject : m_pItems)
	{
		//check if the boundingbox is the same as 1 of the items
		auto boundingboxP = pGameobject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		auto boundingbox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingboxP);

		if (boundingbox == pItemBoundingBox)
		{
			pGameobject->Clear();
			pGameObjectToRemove = pGameobject;

		}

	}

	if (pGameObjectToRemove != nullptr)
	{
		
		m_pItems.remove(pGameObjectToRemove);
	}
}
