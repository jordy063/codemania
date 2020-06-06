#include "MiniginPCH.h"
#include "BoulderManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "BoundingBoxComponent.h"
#include "SpriteComponent.h"
#include "BoulderComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "TileMapLoader.h"


void BoulderManager::MakeBoulder(std::shared_ptr<TransformComponent> transform)
{
	auto pBoulderObject{ std::shared_ptr<dae::GameObject>(new dae::GameObject()) };
	dae::SceneManager::GetInstance().GetActiveScene()->Add(pBoulderObject);

	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/boulders.png", 2, 4, 0, 0.2f, 32, 16));
	auto pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(pBoulderObject->GetTransform(), true, 30.0f));

	auto pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(16, 16, pPhysicsComp));
	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), pPhysicsComp, pBoundingBox));
	auto pBoulderBox = std::shared_ptr<comps::BoulderComponent>(new comps::BoulderComponent(pPhysicsComp));

	
	pBoulderObject->AddComponent(pSpriteComp, ComponentType::SPRITECOMP);
	pBoulderObject->AddComponent(pBoundingBox, ComponentType::BOUNDINGBOXCOMP);
	pBoulderObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	pBoulderObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	pBoulderObject->AddComponent(pBoulderBox, ComponentType::BOULDERCOMPONENT);

	pBoulderObject->GetTransform()->Translate(transform->GetPosition());

}

void BoulderManager::CheckIfHit()
{
	//here we check if the player hits any boulders
}
