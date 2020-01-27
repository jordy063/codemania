#include "MiniginPCH.h"
#include "GameObject.h"
#include "Player.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"


Player::Player()
{
	CreateEntityObject();

	CreateComponents();
}

void Player::CreateComponents()
{
	
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/characterWalk.png", 4, 4, 0, 4, 0.2f));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform()));

	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(physicsComp);
}
