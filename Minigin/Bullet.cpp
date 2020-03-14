#include "MiniginPCH.h"
#include "Bullet.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

Bullet::Bullet(comps::Direction direction, float speed)
	:m_Direction{ direction }
	, m_Speed{ speed }
{
	CreateEntityObject();

	CreateComponents();
}

void Bullet::CreateComponents()
{
	float defaultSpeed{ 20.0f };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/flame.png", 1, 7, 0, 6, 0.2f));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), defaultSpeed));

	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(physicsComp);

	physicsComp->SetMovement(m_Direction, m_Speed);
}
