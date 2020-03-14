#include "MiniginPCH.h"
#include "GameObject.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"


Player::Player()
{
	CreateEntityObject();

	CreateComponents();
}

void Player::CreateComponents()
{
	
	float defaultSpeed{ 100 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/characterWalk.png", 4, 4, 0, 4, 0.2f));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), defaultSpeed));
	auto inputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(physicsComp, spriteComp));


	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(physicsComp);
	m_EntityObject->AddComponent(inputComp);
}
