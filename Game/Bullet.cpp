#include "MiniginPCH.h"
#include "Bullet.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include "Scene.h"
#include "TileMapLoader.h"

Bullet::Bullet(comps::Direction direction, float speed, std::shared_ptr<dae::Scene> scene,int id)
	:m_Direction{ direction }
	, m_Speed{ speed }


{
	CreateEntityObject();
	scene->Add(m_EntityObject);
	CreateComponents(id,scene);
}

void Bullet::CreateComponents(int id,std::shared_ptr<dae::Scene> scene)
{
	float defaultSpeed{ 20.0f };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Bubble.png", 4, 8,id,0.2f,16,16));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(),false, defaultSpeed));
	m_pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionWalls(1),
		scene->GetTileMap()->GetCollisionPlatforms(1), physicsComp, 16, 16));

	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(m_pBoundingBox);
	m_EntityObject->AddComponent(physicsComp);

	physicsComp->SetMovement(m_Direction, m_Speed);
	spriteComp->SetBeginEndFrames(id * 8,7 + id * 8);
}

