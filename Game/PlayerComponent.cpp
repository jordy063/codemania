#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "PhysicsComponent.h"
#include "BoundingBoxComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "Scene.h"
#include "TileMapLoader.h"
#include "CollisionComponent.h"

PlayerComponent::PlayerComponent(int controllerId, int spriteId)
    :m_ControllerId(controllerId)
    ,m_SpriteId(spriteId)
{
}

void PlayerComponent::Initialize(const dae::Scene& scene)
{
    UNREFERENCED_PARAMETER(scene);
	auto playerObject = std::shared_ptr<dae::GameObject>();

	
	float movementSpeed{ 100 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/CharacterSprite.png", 13, 8, m_SpriteId, 0.2f, 32, 32));
	m_pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(playerObject->GetTransform(), true, movementSpeed));
	auto inputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(m_pPhysicsComp, spriteComp, m_ControllerId));
	//m_pBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene.GetTileMap()->GetCollisionWalls(1), scene.GetTileMap()->GetCollisionPlatforms(1), m_pPhysicsComp, 16, 16));

	m_pBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(16, 16, m_pPhysicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene.GetTileMap()->GetCollisionWalls(),
		scene.GetTileMap()->GetCollisionPlatforms(), m_pPhysicsComp, m_pBoundingBoxComp));

	playerObject->AddComponent(spriteComp, ComponentType::SPRITECOMP);
	playerObject->AddComponent(m_pBoundingBoxComp, ComponentType::BOUNDINGBOXCOMP);
	playerObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	playerObject->AddComponent(m_pPhysicsComp, ComponentType::PHYSICSCOMP);
	playerObject->AddComponent(inputComp, ComponentType::INPUTCOMPONENT);
}

void PlayerComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
    UNREFERENCED_PARAMETER(scene);
    UNREFERENCED_PARAMETER(elapsedSecs);
    UNREFERENCED_PARAMETER(pos);
}

void PlayerComponent::TakeDamage()
{
}


