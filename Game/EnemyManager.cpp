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
	//for all enemies update and check if an enemy hits the avatar

	/*for (std::shared_ptr <Enemy> enemy : m_pEnemies)
	{
		enemy->Update(elapsedSecs, player);
		
	}*/

}

int EnemyManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox,int& index)
{
	UNREFERENCED_PARAMETER(pBulletBoundingBox);
	//GetBoundingBoxOfBullet and check with all enemies
	//pBullet->

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

void EnemyManager::RegisterPlayer(std::shared_ptr<dae::GameObject> playerObject)
{
	m_pPlayerObject = playerObject;
}

void EnemyManager::MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene)
{


	//enemy test
	MakeGhost({ 100, 100 }, scene);

	//enemy test2

	MakeZenChan({ 150, 100 }, scene);
	

}

void EnemyManager::MakeZenChan(float2 pos, std::shared_ptr<dae::Scene> scene)
{

	EnemyObserver::GetInstance().UpCounter();

	auto enemyObject = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	scene->Add(enemyObject);
	enemyObject->GetTransform()->Translate(pos.x, pos.y);

	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8, 0, 0.2f, 44, 22));
	auto pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(enemyObject->GetTransform(), true, 30.0f));

	auto pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22, pPhysicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene->GetTileMap()->GetCollisionWalls(),
		scene->GetTileMap()->GetCollisionPlatforms(), pPhysicsComp,pBoundingBox));
	auto pZenChanAiComp = std::shared_ptr<comps::ZenChanAIComponent>(new comps::ZenChanAIComponent(m_pPlayerObject, pSpriteComp, pPhysicsComp, pBoundingBox));

	//add AIcomponent and do the same as in playerclass

	enemyObject->AddComponent(pSpriteComp, ComponentType::SPRITECOMP);
	enemyObject->AddComponent(pBoundingBox, ComponentType::BOUNDINGBOXCOMP);
	enemyObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	enemyObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	enemyObject->AddComponent(pZenChanAiComp, ComponentType::ZENCHANCOMPONENT);
	

	m_pEnemies.push_back({ enemyObject,ItemType::FRIES });
}
void EnemyManager::MakeGhost(float2 pos, std::shared_ptr<dae::Scene> scene)
{
	EnemyObserver::GetInstance().UpCounter();
	auto enemyObject = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	scene->Add(enemyObject);
	enemyObject->GetTransform()->Translate(pos.x, pos.y);

	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8, 1, 0.2f, 44, 22));
	auto pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(enemyObject->GetTransform(), false, 30.0f));
	auto pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22, pPhysicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene->GetTileMap()->GetCollisionWalls(),
		scene->GetTileMap()->GetCollisionPlatforms(), pPhysicsComp, pBoundingBox));
	auto ghostAiComp = std::shared_ptr<comps::GhostAIComponent>(new comps::GhostAIComponent(m_pPlayerObject, pSpriteComp, pPhysicsComp, pBoundingBox));

	//add AIcomponent and do the same as in playerclass

	enemyObject->AddComponent(pSpriteComp, ComponentType::SPRITECOMP);
	enemyObject->AddComponent(pBoundingBox, ComponentType::BOUNDINGBOXCOMP);
	enemyObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	enemyObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	enemyObject->AddComponent(ghostAiComp, ComponentType::GHOSTAICOMPONENT);

	m_pEnemies.push_back({ enemyObject,ItemType::MELON });
}

