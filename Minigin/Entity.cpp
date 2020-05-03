#include "MiniginPCH.h"
#include "Entity.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "BoundingBoxComponent.h"

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
rectangle_ Entity::GetBoundingBox() const
{
	return m_pBoundingBox->GetBoundingBox(0, false);
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

bool Entity::IsOverlapping(std::shared_ptr<Entity> subject)
{
	//if the character and enemy overlap we return true, else false
	rectangle_ playerHitBox = subject->GetBoundingBox();
	rectangle_ enemyHitBox = m_pBoundingBox->GetBoundingBox(0, false);

	auto playerLeft = playerHitBox.posX;
	auto playerRight = playerHitBox.posX + playerHitBox.width;
	auto playerTop = playerHitBox.posY;
	auto playerBottom = playerHitBox.posY + playerHitBox.height;

	auto enemyLeft = enemyHitBox.posX;
	auto enemyRight = enemyHitBox.posX + enemyHitBox.width;
	auto enemyTop = enemyHitBox.posY;
	auto enemyBottom = enemyHitBox.posY + enemyHitBox.height;

	if (enemyLeft < playerRight && playerLeft < enemyRight && playerTop < enemyBottom && enemyTop < playerBottom)
	{
		return true;
	}
	return false;
}
