#include "MiniginPCH.h"
#include "GameObject.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "BoundingBoxComponent.h"
#include "Scene.h"


Player::Player( int controllerId, std::shared_ptr<dae::Scene> scene)
{
	CreateEntityObject();
	scene->Add(m_EntityObject);
	CreateComponents(controllerId,scene);
}

void Player::CreateComponents( int controllerId , std::shared_ptr<dae::Scene> scene)
{
	
	float movementSpeed{ 100 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/characterWalk.png", 4, 4, 0, 4, 0.2f,32,32));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), true , movementSpeed));
	auto inputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(physicsComp, spriteComp, controllerId));
	auto boundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionTiles(),physicsComp,16,28));


	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(boundingBoxComp);
	m_EntityObject->AddComponent(physicsComp);
	m_EntityObject->AddComponent(inputComp);
}
