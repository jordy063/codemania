#include "MiniginPCH.h"
#include "Bullet.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

Bullet::Bullet(comps::Direction direction, float speed, std::shared_ptr<dae::Scene> scene)
	:m_Direction{ direction }
	, m_Speed{ speed }
{
	CreateEntityObject();
	scene->Add(m_EntityObject);
	CreateComponents();
}

void Bullet::CreateComponents()
{
	float defaultSpeed{ 20.0f };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/flame.png", 1, 7, 0, 6, 0.2f,16,16));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(),false, defaultSpeed));

	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(physicsComp);

	physicsComp->SetMovement(m_Direction, m_Speed);
}
