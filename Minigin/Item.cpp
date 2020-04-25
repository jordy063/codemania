#include "MiniginPCH.h"
#include "Item.h"
#include "Player.h"
#include "BoundingBoxComponent.h"
#include "SpriteComponent.h"

Item::Item(std::shared_ptr<dae::Scene> scene, int level, int id)
{
	CreateComponents(scene, level, id);
}
void Item::CreateComponents(std::shared_ptr<dae::Scene> scene, int level,int id)
{
	int collsPerRow{ 8 };
	pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8, 0 + id * collsPerRow, 8 + id * collsPerRow, 0.2f, 16, 16));
	pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_EntityObject->GetTransform(), true, 0));
	m_pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene->GetTileMap()->GetCollisionWalls(level),
		scene->GetTileMap()->GetCollisionPlatforms(level), pPhysicsComp, 16, 16));

	//add AIcomponent and do the same as in playerclass


	m_EntityObject->AddComponent(pSpriteComp);
	m_EntityObject->AddComponent(m_pBoundingBox);
	m_EntityObject->AddComponent(pPhysicsComp);
}

void Item::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	//if it's overlapping, spawn the text that acts as a particle effect add the points to player
	
}

bool Item::IsOverlapping(std::shared_ptr<Player> player)
{
	//if the character and enemy overlap we return true, else false
	rectangle_ playerHitBox = player->GetBoundingBox();
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
