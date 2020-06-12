#include "MiniginPCH.h"
#include "EnemyManager.h"
#include "Scene.h"
#include "BoundingBoxComponent.h"
#include "GhostAIComponent.h"
#include "GameObject.h"
#include "ZenChanAIComponent.h"
#include "CollisionComponent.h"
#include "EnemyObserver.h"
#include "MaitaAIComponent.h"
#include "TileMapLoader.h"


void EnemyManager::MakeEnemies(std::shared_ptr<dae::Scene> scene,int level)
{
	
	//make enemies according to the level given
	switch (level)
	{
	case 0:
		MakeEnemiesLevel0(scene);
		break;
	case 1:
		MakeEnemiesLevel1(scene);
		break;
	case 2:
		MakeEnemiesLevel2(scene);
		break;

	default:
		break;
	}

}

void EnemyManager::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);

}

int EnemyManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBulletBoundingBox,int& index, std::shared_ptr<dae::GameObject>& other)
{
	UNREFERENCED_PARAMETER(pBulletBoundingBox);
	
	//check if the bullet overlaps with an enemy
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
			enemy.first->Disable();
			other = enemy.first;
			return enemy.second;
		}
	}
	return -1;
}

void EnemyManager::RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers)
{
	
	m_pPlayerObjects = pPlayers;
}

void EnemyManager::AddEnemyToList(std::pair<std::shared_ptr<dae::GameObject> ,EnemyType> pEnemy)
{
	//we remove the enemy when we change our bullet so it doesn't check if it's hit anymore
	m_pEnemies.push_back(pEnemy);
}

void EnemyManager::RemoveEnemies()
{
	for (std::pair < std::shared_ptr<dae::GameObject>, int> pEnemy : m_pEnemies)
	{
		pEnemy.first->Clear();
	}
	
	m_pEnemies.clear();
}

void EnemyManager::MakeEnemiesLevel0(std::shared_ptr<dae::Scene> scene)
{


	//enemy test
	//MakeEnemy({ 100,100 }, scene, EnemyType::GHOST);
	//

	////enemy test2
	//MakeEnemy({ 150,100 }, scene, EnemyType::ZENCHAN);
	//enemy test
	//MakeEnemy({ 300,100 }, scene, EnemyType::GHOST);


	////enemy test2
	//MakeEnemy({ 150,100 }, scene, EnemyType::ZENCHAN);



	MakeEnemy({ 250,100 }, scene, EnemyType::MAITA,comps::Direction::RIGHT);

}
void EnemyManager::MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene)
{
	scene->GetTileMap()->UpdateLevel(1);

	////enemy test
	MakeEnemy({ 300,700 }, scene, EnemyType::GHOST, comps::Direction::RIGHT);

	MakeEnemy({ 500,900 }, scene, EnemyType::GHOST, comps::Direction::LEFT);
	MakeEnemy({ 100,900 }, scene, EnemyType::GHOST, comps::Direction::RIGHT);



	////enemy test2
	MakeEnemy({ 200,700 }, scene, EnemyType::ZENCHAN, comps::Direction::LEFT);


	MakeEnemy({ 250,700 }, scene, EnemyType::MAITA,comps::Direction::RIGHT);

}
void EnemyManager::MakeEnemiesLevel2(std::shared_ptr<dae::Scene> scene)
{
	scene->GetTileMap()->UpdateLevel(2);

	//enemy test
	MakeEnemy({ 100,1400 }, scene, EnemyType::GHOST, comps::Direction::LEFT);
	MakeEnemy({ 500,1400 }, scene, EnemyType::GHOST, comps::Direction::RIGHT);


	//enemy test2
	MakeEnemy({ 150,1400 }, scene, EnemyType::ZENCHAN, comps::Direction::LEFT);
	MakeEnemy({ 300,1400 }, scene, EnemyType::ZENCHAN, comps::Direction::RIGHT);


	MakeEnemy({ 250,1400 }, scene, EnemyType::MAITA, comps::Direction::RIGHT);
	MakeEnemy({ 400,1400 }, scene, EnemyType::MAITA, comps::Direction::LEFT);
}


void EnemyManager::MakeEnemy(float2 pos, std::shared_ptr<dae::Scene> scene,EnemyType type,comps::Direction direction)
{
	//we upcount our enemyamount
	EnemyObserver::GetInstance().UpCounter();

	//make the actual opject.
	auto enemyObject = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	
	enemyObject->GetTransform()->Translate(pos.x, pos.y);

	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/EnemySheet.png", 6, 8, type, 0.2f, 44, 22));

	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp;
	//everything but ghost has gravity enabled
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

	//we add a different AI component according to the enemy type
	if (type == EnemyType::ZENCHAN)
	{
		auto pZenChanAiComp{ std::shared_ptr<comps::ZenChanAIComponent>(new comps::ZenChanAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox,direction)) };
		enemyObject->AddComponent(pZenChanAiComp, ComponentType::ZENCHANCOMPONENT);
	}
	else if (type == EnemyType::GHOST)
	{
		auto ghostAiComp = std::shared_ptr<comps::GhostAIComponent>(new comps::GhostAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox, direction));
		enemyObject->AddComponent(ghostAiComp, ComponentType::GHOSTAICOMPONENT);
	}
	if (type == EnemyType::MAITA)
	{
		auto pMaitaAiComp{ std::shared_ptr<comps::MaitaAIComponent>(new comps::MaitaAIComponent(m_pPlayerObjects, pSpriteComp, pPhysicsComp, pBoundingBox,direction)) };
		enemyObject->AddComponent(pMaitaAiComp, ComponentType::MAITAAICOMPNENT);

	}
	//according to our enemy type we also add the right itemType
	auto itemType = static_cast<ItemType>(type);
	m_pEnemies.push_back({ enemyObject,itemType });

	
	scene->Add(enemyObject);
	enemyObject->Initialize();

}
