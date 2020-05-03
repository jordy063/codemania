#include "MiniginPCH.h"
#include "Item.h"
#include "Player.h"
#include "BoundingBoxComponent.h"
#include "SpriteComponent.h"

Item::Item(std::shared_ptr<dae::Scene> scene, int level, int id)
{
	CreateComponents(scene, level, id);
}
void Item::CreateComponents(std::shared_ptr<dae::Scene> scene, int level,int id)
{
	
	pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8,id, 0.2f, 16, 16));
	pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), true, 0));
	m_pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionWalls(level),
		scene->GetTileMap()->GetCollisionPlatforms(level), pPhysicsComp, 16, 16));

	//add AIcomponent and do the same as in playerclass


	m_EntityObject->AddComponent(pSpriteComp);
	m_EntityObject->AddComponent(m_pBoundingBox);
	m_EntityObject->AddComponent(pPhysicsComp);
}

void Item::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	//if it's overlapping, spawn the text that acts as a particle effect add the points to player

	
}

