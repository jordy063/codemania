#include "MiniginPCH.h"
#include "GameObject.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "BoundingBoxComponent.h"


Player::Player(const std::shared_ptr< TileMapLoader> tilemap)
{
	CreateEntityObject();

	CreateComponents(tilemap);
}

void Player::CreateComponents(const std::shared_ptr< TileMapLoader> tilemap)
{
	
	float movementSpeed{ 100 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/characterWalk.png", 4, 4, 0, 4, 0.2f,32,32));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), movementSpeed));
	auto inputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(physicsComp, spriteComp));
	auto boundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(tilemap->GetCollisionTiles(),physicsComp,16,28));


	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(boundingBoxComp);
	m_EntityObject->AddComponent(physicsComp);
	m_EntityObject->AddComponent(inputComp);
}
