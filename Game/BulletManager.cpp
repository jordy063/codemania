#include "MiniginPCH.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "Bullet.h"
#include "GameObject.h"
#include "EnemyManager.h"
#include "SpriteComponent.h"
#include "BoundingBoxComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TileMapLoader.h"
#include "BubbleComponent.h"
#include "CollisionComponent.h"

void BulletManager::MakeBullet(const float2& position, comps::Direction direction, int id)
{
	//make the component and at it too current scene
	//auto pos = physicsComp->GetTransform()->GetPosition();
	/*auto bullet = std::shared_ptr<Bullet>(new Bullet(direction, speed, dae::SceneManager::GetInstance().GetActiveScene(), id));

	bullet->GetGameObject()->GetTransform()->Translate(position.x, position.y);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(bullet->GetGameObject());

	m_pBullets.push_back(bullet);*/
	auto bulletObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	dae::SceneManager::GetInstance().GetActiveScene()->Add(bulletObject);

	bulletObject->GetTransform()->Translate(position);

	float defaultSpeed{ 20.0f };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Bubble.png", 4, 8, id, 0.2f, 16, 16));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(bulletObject->GetTransform(), false, defaultSpeed));

	auto BoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(16, 16, physicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), physicsComp, BoundingBox));
	auto bubbleComp = std::shared_ptr<comps::BubbleComponent>(new comps::BubbleComponent(physicsComp,BoundingBox,pCollisionComp,spriteComp,direction,id));

	bulletObject->AddComponent(spriteComp, ComponentType::SPRITECOMP);
	bulletObject->AddComponent(BoundingBox, ComponentType::BOUNDINGBOXCOMP);
	bulletObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	bulletObject->AddComponent(physicsComp, ComponentType::PHYSICSCOMP);
	bulletObject->AddComponent(bubbleComp, ComponentType::BUBBLECOMPONENT);

	m_pBullets.push_back(bulletObject);

	//this has to be in a component allong with overrlap of character
	/*physicsComp->SetMovement(direction, m_Speed);
	spriteComp->SetBeginEndFrames(id * 8, 7 + id * 8);*/
}

void BulletManager::RegisterPlayer(std::shared_ptr<dae::GameObject> pPlayerObject)
{
	
	auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
	m_pPlayerBoundingBox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp);
}

void BulletManager::Update()
{
	//for all enemies check if they overlap
	/*for (std::shared_ptr<Bullet> bullet : m_pBullets)
	{
		EnemyManager::GetInstance().CheckIfHit(bullet);
	}*/

	//if they do change the enemy to a different sprite depending on the type Also set it in a certain state
	//while in that state it goes up for a small amount of time and has collision
}

void BulletManager::AddBoundingBoxToList(std::shared_ptr<comps::CollisionComponent> pCollisionComp, std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
{
	
	m_pTriggeredBullets.push_back(pBoundingBox);
	
	
	for (std::shared_ptr<comps::BoundingBoxComponent> boundingBox : m_pTriggeredBullets)
	{
		//we need all boundingboxes 
		pCollisionComp->SetExtraCollisions(m_pTriggeredBullets);
		//set the current list of boundingboxes in the boundingboxcomp
	}
}

void BulletManager::RemoveBullet(std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
{
	//get the boundingboxcomp of every gameobject and check if those boundingboxes are the same
	//here we should update the collision comp of every gameobject
	m_pTriggeredBullets.remove(pBoundingBox);
	std::shared_ptr<dae::GameObject> pGameObjectToRemove{ nullptr };

	for (std::shared_ptr<dae::GameObject> pGameObject : m_pBullets)
	{
		
		auto boundingboxP = pGameObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		auto boundingbox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingboxP);

		if (boundingbox == pBoundingBox)
		{
			pGameObject->Clear();
			pGameObjectToRemove = pGameObject;
			
		}
	}
	if (pGameObjectToRemove != nullptr)
	{
		m_pBullets.remove(pGameObjectToRemove);
	}

	for (std::shared_ptr<dae::GameObject> pGameObject : m_pBullets)
	{
		auto collisionP = pGameObject->GetComponent(ComponentType::COLLISIONCOMPONENT);
		auto collision = std::dynamic_pointer_cast<comps::CollisionComponent>(collisionP);


			//we need all boundingboxes 
			collision->SetExtraCollisions(m_pTriggeredBullets);
			//set the current list of boundingboxes in the boundingboxcomp
		
	}



}

bool BulletManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox)
{
	//checks if player and current bullet overlap
	
	return m_pPlayerBoundingBox->IsOverlapping(pBulletBoundingBox);
	
}
