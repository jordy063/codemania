#include "MiniginPCH.h"
#include "AI.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "AIComponent.h"
#include "Scene.h"
#include "BoundingBoxComponent.h"
#include "EnemyObserver.h"
AI::AI(std::shared_ptr<dae::Scene> scene)
{
	CreateEntityObject();
	scene->Add(m_EntityObject);
	CreateComponents(scene);
	EnemyObserver::GetInstance().UpCounter();
}


void AI::CreateComponents(std::shared_ptr<dae::Scene> scene)
{

	float walkSpeed{ 20 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/characterWalk.png", 4, 4, 0, 4, 0.2f,16,16));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(),true , walkSpeed));
	auto aiComponent = std::shared_ptr<comps::AIComponent>(new comps::AIComponent(physicsComp, spriteComp));
	auto boundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionTiles(), physicsComp, 16, 28));

	//add AIcomponent and do the same as in playerclass
	

	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(boundingBoxComp);
	m_EntityObject->AddComponent(physicsComp);
	m_EntityObject->AddComponent(aiComponent);

}

void AI::ClearAI()
{
	m_EntityObject->Clear();
	EnemyObserver::GetInstance().DownCounter();
}

