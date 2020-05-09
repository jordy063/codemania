#include "MiniginPCH.h"
#include "GameObject.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "BoundingBoxComponent.h"
#include "Scene.h"
#include "CollisionComponent.h"


Player::Player( int controllerId,int spriteId, std::shared_ptr<dae::Scene> scene)
	:m_Health(3)
	, screenDeathPosition{ 50.0f,300.0f }
{
	CreateEntityObject();
	
	scene->Add(m_EntityObject);
	CreateComponents(controllerId,spriteId,scene);
	
}

void Player::CreateComponents( int controllerId ,int spriteId, std::shared_ptr<dae::Scene> scene)
{
	
	float movementSpeed{ 100 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/CharacterSprite.png", 13, 8,spriteId, 0.2f,32,32));
	m_pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), true , movementSpeed));
	auto inputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(m_pPhysicsComp, spriteComp, controllerId));
	//m_pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionWalls(1), scene->GetTileMap()->GetCollisionPlatforms(1), m_pPhysicsComp,16,16));
	m_pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(16, 16, m_pPhysicsComp));

	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene->GetTileMap()->GetCollisionWalls(1),
		scene->GetTileMap()->GetCollisionPlatforms(1), m_pPhysicsComp, m_pBoundingBox));

	m_EntityObject->AddComponent(spriteComp,ComponentType::SPRITECOMP);
	m_EntityObject->AddComponent(m_pBoundingBox,ComponentType::BOUNDINGBOXCOMP);
	m_EntityObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	m_EntityObject->AddComponent(m_pPhysicsComp, ComponentType::PHYSICSCOMP);
	m_EntityObject->AddComponent(inputComp, ComponentType::INPUTCOMPONENT);

}

void Player::Update(float elapsedSecs)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	if (IsInvinsible)
	{
		//set a timer, per 0.5 secs we change a bool so that the set texture changes
		//if the timer is over we set invinsible back to false
	}
}



void Player::TakeDamage()
{
	if (IsInvinsible == false)
	{
		if (m_Health > 0)
		{
			--m_Health;
		}
		//also teleport player to the beginning and set the state to flickering for a small amount of time. if it's flickering the player can't take damage
		GetGameObject()->GetTransform()->Translate(screenDeathPosition);
		IsInvinsible = true;
	}
}

bool Player::IsAirBorne()
{
	return m_pPhysicsComp->GetAirBorne();;
}

