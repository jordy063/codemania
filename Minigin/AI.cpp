#include "MiniginPCH.h"
#include "AI.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "AIComponent.h"
AI::AI()
{
	CreateEntityObject();

	CreateComponents();
}

void AI::CreateComponents()
{

	float walkSpeed{ 20 };
	auto spriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/characterWalk.png", 4, 4, 0, 4, 0.2f,16,16));
	auto physicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), walkSpeed));
	auto aiComponent = std::shared_ptr<comps::AIComponent>(new comps::AIComponent(physicsComp, spriteComp));

	//add AIcomponent and do the same as in playerclass
	

	m_EntityObject->AddComponent(spriteComp);
	m_EntityObject->AddComponent(physicsComp);
	m_EntityObject->AddComponent(aiComponent);

}

