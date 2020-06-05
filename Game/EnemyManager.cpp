#include "MiniginPCH.h"
#include "EnemyManager.h"
#include "Ghost.h"
#include "Scene.h"
#include "ZenChan.h"
#include "Bullet.h"
#include "BoundingBoxComponent.h"
#include "GhostAIComponent.h"
#include "GameObject.h"
#include "ZenChanAIComponent.h"
#include "CollisionComponent.h"
#include "EnemyObserver.h"
#include "MaitaAIComponent.h"


void EnemyManager::MakeEnemies(std::shared_ptr<dae::Scene> scene,int level)
{
	//OPTION 1
	//we check how how enemies we currently have and see if we need more of that type
	switch (level)
	{
	case 1:
		MakeEnemiesLevel1(scene);
		break;
	case 2:
		break;
	case 3:
		break;

	default:
		break;
	}


	//OPTION 2
	//we make all enemies and add them to the scene
	//we just create new enemies every time
}

void EnemyManager::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);

}

int EnemyManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox,int& index)
{
	UNREFERENCED_PARAMETER(pBulletBoundingBox);
	//GetBoundingBoxOfBullet and check with all enemies

	for (std::pair<std::shared_ptr<dae::GameObject>,int> enemy : m_pEnemies)
	{

		auto boundingBoxComp = enemy.first->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		auto actualBoundingBox = std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp);

		if (actualBoundingBox->IsOverlapping(pBulletBoundingBox))
		{
			auto spriteComp = enemy.first->GetComponent(ComponentType::SPRITECOMP);
			auto actualSpriteComp = std::dynamic_pointer_cast<comps::SpriteComponent>(spriteComp);

			index = actualSpriteComp->GetSpriteIndex();

			//the enemy is hit so we can turn it into a bubble and clear our bullet
			m_pEnemies.remove(enemy);
			enemy.first->Clear();
			return enemy.second;
		}
	}
	return -1;
}

void EnemyManager::RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers)
{
	
	m_pPlayerObjects = pPlayers;
}

void EnemyManager::MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene)
{


	//enemy test
	MakeEnemy({ 100,100 }, scene, EnemyType::GHOST);
	

	//enemy test2
	MakeEnemy({ 150,100 }, scene, EnemyType::ZENCHAN);
	

	MakeEnemy({ 250,100 }, scene, EnemyType::MAITA);
	

}


void EnemyManager::MakeEnemy(float2 pos, std::shared_ptr<dae::Scene> scene,EnemyType type)
{
	EnemyObserver::GetInstance().UpCounter();
	auto enemyObject = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	scene->Add(enemyObject);
	enemyObject->GetTransform()->Translate(pos.x, pos.y);

	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/EnemySheet.png", 6, 8, type, 0.2f, 44, 22));

	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp;
	if (type == EnemyType::GHOST)
	{
		pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(enemyObject->GetTransform(), false, 30.0f));
	}
	else
	{
		pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(enemyObject->GetTransform(), true, 30.0f));
	}

	
	auto pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22, pPhysicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene->GetTileMap()->GetCollisionWalls(),
		scene->GetTileMap()->GetCollisionPlatforms(), pPhysicsComp, pBoundingBox));

	enemyObject->AddComponent(pSpriteComp, ComponentType::SPRITECOMP);
	enemyObject->AddComponent(pBoundingBox, ComponentType::BOUNDINGBOXCOMP);
	enemyObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	enemyObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	if (type == EnemyType::ZENCHAN)
	{
		auto pZenChanAiComp{ std::shared_ptr<comps::ZenChanAIComponent>(new comps::ZenChanAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox)) };
		enemyObject->AddComponent(pZenChanAiComp, ComponentType::ZENCHANCOMPONENT);
	}
	else if (type == EnemyType::GHOST)
	{
		auto ghostAiComp = std::shared_ptr<comps::GhostAIComponent>(new comps::GhostAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox));
		enemyObject->AddComponent(ghostAiComp, ComponentType::GHOSTAICOMPONENT);
	}
	if (type == EnemyType::MAITA)
	{
		auto pMaitaAiComp{ std::shared_ptr<comps::MaitaAIComponent>(new comps::MaitaAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox)) };
		enemyObject->AddComponent(pMaitaAiComp, ComponentType::MAITAAICOMPNENT);
	}
	auto itemType = static_cast<ItemType>(type);
	m_pEnemies.push_back({ enemyObject,itemType });

	/*switch (type)
	{
	case ZENCHAN:
		auto pZenChanAiComp{ std::shared_ptr<comps::ZenChanAIComponent>(new comps::ZenChanAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox) };
		enemyObject->AddComponent(pZenChanAiComp, ComponentType::ZENCHANCOMPONENT);
		break;
	case GHOST:
		auto ghostAiComp = std::shared_ptr<comps::GhostAIComponent>(new comps::GhostAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox));
		enemyObject->AddComponent(ghostAiComp, ComponentType::GHOSTAICOMPONENT);
		break;
	case MAITA:
		break;
	default:
		break;
	}*/
	

	//add AIcomponent and do the same as in playerclass

	
	

	
}
