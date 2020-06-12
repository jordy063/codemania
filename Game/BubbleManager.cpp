#include "MiniginPCH.h"
#include "BubbleManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "EnemyManager.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TileMapLoader.h"
#include "BubbleComponent.h"
#include "CollisionComponent.h"


void BubbleManager::MakeBullet(const float2& position, comps::Direction direction, int id)
{
	//here we make the object and add the rigth components

	auto bulletObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	dae::SceneManager::GetInstance().GetActiveScene()->Add(bulletObject);

	bulletObject->GetTransform()->Translate(position);
	
	float defaultSpeed{ 20.0f };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Bubble.png", 5, 8, id, 0.2f, 40, 20));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(bulletObject->GetTransform(), false, defaultSpeed));

	auto BoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(20, 20, physicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), physicsComp, BoundingBox));
	auto bubbleComp = std::shared_ptr<comps::BubbleComponent>(new comps::BubbleComponent(physicsComp,BoundingBox,pCollisionComp,spriteComp,direction,id,int( m_pPlayerBoundingBoxes.size())));

	bulletObject->AddComponent(spriteComp, ComponentType::SPRITECOMP);
	bulletObject->AddComponent(BoundingBox, ComponentType::BOUNDINGBOXCOMP);
	bulletObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	bulletObject->AddComponent(physicsComp, ComponentType::PHYSICSCOMP);
	bulletObject->AddComponent(bubbleComp, ComponentType::BUBBLECOMPONENT);

	//when it's done we at it to the list
	m_pBullets.push_back(bulletObject);

}

void BubbleManager::RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers)
{
	//register the components needed during the game
	for (std::shared_ptr<dae::GameObject> pPlayerObject : pPlayers)
	{
		auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

		auto physicsComp = pPlayerObject->GetComponent(ComponentType::PHYSICSCOMP);
		m_pPlayerPhysicsComps.push_back(std::dynamic_pointer_cast<comps::PhysicsComponent>(physicsComp));
	}
}


void BubbleManager::AddBoundingBoxToList(std::shared_ptr<comps::CollisionComponent> pCollisionComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
{
	//this gets called a bit after the bullet is made
	//this happens because we don't want the player to collide with the bullet instantly

	m_pTriggeredBullets.push_back(pBoundingBox);
	
	for (std::shared_ptr<comps::BoundingBoxComponent> boundingBox : m_pTriggeredBullets)
	{
		//for all bulletBoundingboxes
		//set the current list of boundingboxes in the boundingboxcomp
		pCollisionComp->SetExtraCollisions(m_pTriggeredBullets);
		
	}
}

void BubbleManager::RemoveBullet(std::shared_ptr<comps::CollisionComponent> pCollisionComp,std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
{
	
	m_pTriggeredBullets.remove(pBoundingBox);
	

	std::shared_ptr<dae::GameObject> pGameObjectToRemove{ nullptr };
	
	//we check which bullet it is
	for (std::shared_ptr<dae::GameObject> pGameObject : m_pBullets)
	{
		
		auto boundingboxP = pGameObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		auto boundingbox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingboxP);

		if (boundingbox == pBoundingBox)
		{
			//we disable it instead of clear because we still want it back
			pGameObject->Disable();
			pGameObjectToRemove = pGameObject;
			
		}
	}
	//remove the object we captured
	if (pGameObjectToRemove != nullptr)
	{
		m_pBullets.remove(pGameObjectToRemove);
	}

	//after removing the bullet we update the extra collision in our collisioncomps
	for (std::shared_ptr<dae::GameObject> pGameObject : m_pBullets)
	{
		auto collisionP = pGameObject->GetComponent(ComponentType::COLLISIONCOMPONENT);
		auto collision = std::dynamic_pointer_cast<comps::CollisionComponent>(collisionP);

		//for all collisionComps
		//update the collisioncomps with the changed list of boundingboxes
		collision->SetExtraCollisions(m_pTriggeredBullets);
	
	}

}

HitType BubbleManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox,int playerId)
{
	//checks if player and current bullet overlap
	
	bool isHit{ m_pPlayerBoundingBoxes[playerId]->IsOverlapping(pBulletBoundingBox) };
	if (isHit)
	{
		//find the bullet you're standing on
		if (pBulletBoundingBox->GetBoundingBox(0, false).posY - pBulletBoundingBox->GetBoundingBox(0, false).height + 1 < m_pPlayerBoundingBoxes[playerId]->GetBoundingBox(0, false).posY)
		{
			//destroy the current bubble
			return HitType::SIDEHIT;

		}
		else
		{
			//move the player on the bubble
			return HitType::UPHIT;
		}
	}
	
	return HitType::NOHIT;

	
}

bool BubbleManager::CheckPlayer2HitsBullet()
{
	//check if player 2 is hit. this only gets called when in versus mode
	for (std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox : m_pTriggeredBullets)
	{
		bool isHit{ m_pPlayerBoundingBoxes[1]->IsOverlapping(pBulletBoundingBox) };
		if (isHit)
		{
			return true;
		}
	}
	return false;
}

void BubbleManager::MovePlayerWithBullet(int playerId)
{
	m_pPlayerPhysicsComps[playerId]->SetSpeedY(-m_BulletSpeed.y);
}

void BubbleManager::Reset()
{
	m_pPlayerBoundingBoxes.clear();
	m_pPlayerPhysicsComps.clear();
}
