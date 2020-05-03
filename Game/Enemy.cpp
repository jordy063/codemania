#include "MiniginPCH.h"
#include "Enemy.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "Scene.h"
#include "BoundingBoxComponent.h"
#include "EnemyObserver.h"
#include "Player.h"

int Enemy::m_Seed = 0;

Enemy::Enemy(std::shared_ptr<dae::Scene> scene, int level,int id, bool gravity)
	:m_IsAlive(true)
	, m_Speed{ 30.0f,0 }
	, m_CurrentDirection(comps::Direction::RIGHT)
{
	CreateEntityObject();
	scene->Add(m_EntityObject);
	CreateComponents(scene,level,id,gravity);
	EnemyObserver::GetInstance().UpCounter();


	std::srand(m_Seed);
	++m_Seed;
	DirToRow[comps::Direction::LEFT] = 3;
	DirToRow[comps::Direction::RIGHT] = 1;
	DirToRow[comps::Direction::UP] = 2;
	//DirToRow[Direction::DOWN] = 0;

	pSpriteComp->SetActiveRowStop();
}


void Enemy::CreateComponents(std::shared_ptr<dae::Scene> scene,int level,int id, bool gravity)
{
	
	pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8,id,0.2f,16,16));
	pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), gravity, m_Speed.x));
	m_pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionWalls(level),
		scene->GetTileMap()->GetCollisionPlatforms(level), pPhysicsComp, 16, 16));

	//add AIcomponent and do the same as in playerclass
	

	m_EntityObject->AddComponent(pSpriteComp);
	m_EntityObject->AddComponent(m_pBoundingBox);
	m_EntityObject->AddComponent(pPhysicsComp);

}

void Enemy::ClearAI()
{
	m_EntityObject->Clear();
	EnemyObserver::GetInstance().DownCounter();

}

void Enemy::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);
}



