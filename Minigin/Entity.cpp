#include "MiniginPCH.h"
#include "Entity.h"
#include "TextureComponent.h"
#include "GameObject.h"

Entity::Entity()
{
	CreateEntityObject();

	CreateComponents();
}


Entity::~Entity()
{
}

void Entity::Initialize()
{
	
	InitializeEntityObject();

}

void Entity::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);
}

void Entity::Render()
{
	//never gets called
	m_EntityObject->Render();
}
void Entity::CreateEntityObject()
{

	m_EntityObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
}
void Entity::InitializeEntityObject()
{
	m_EntityObject->Initialize();
}
void Entity::CreateComponents()
{

}


