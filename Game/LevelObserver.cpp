#include "MiniginPCH.h"
#include "LevelObserver.h"
#include "Scene.h"
#include "TileMapLoader.h"
#include "CollisionComponent.h"


void LevelObserver::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	//we place the default pos somewhere far away
	//this will update everytime
	m_LvHeight = 256;
	m_CurrentLevel = 0;
	m_Hasmoved = false;
	m_TranslationSpeed = 10;
}

void LevelObserver::Update(const dae::Scene& scene, float elapsedSecs)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	if (m_HasLevelChanged)
	{
		//if we show the menu we play the tilemap (pngs at like -750
		if (m_CurrentLevel == 0 && m_Hasmoved == false)
		{
			m_Hasmoved = true;
			m_HasLevelChanged = false;
			//set all pngtiles to 0,800
			//we don't have to change collision
		}
		else
		{
			//when lv = 1 we instantly set the pngs at the correct location and set the collision
			//pngs and collision are seperate!
			auto limit = m_LvHeight * (m_CurrentLevel - 1);
			if (m_CurrentTranslation.y > limit)
			{
				m_pPlayerCollisionComp->SetCollision(scene.GetTileMap()->GetCollisionWalls(m_CurrentLevel), scene.GetTileMap()->GetCollisionPlatforms(m_CurrentLevel));
				m_pPlayerCollisionComp->SetActive(true);
				m_HasLevelChanged = false;
				//set collision of current lv
				//we should have a function in getTilemap that gives the current lv
				//we have to change the collision of the player everything can stay the same. when we ask the currentlevel when we make the component it should be updated.


				//limit is reached

				//here we set the new collision(only once) -> gettilemap and set walls + platforms
				// all collisioncomps should upgrade their level
			}
			else
			{
				//move pngs only
				m_CurrentTranslation.y += elapsedSecs * m_TranslationSpeed;
				//move all pngs with a certain amount
				MoveTilemap({ m_CurrentTranslation });
			}
			// if limit-m_limits
		}
	}

	//if needed the first time the currentlevel is 1 we translate the lv somewhere above the screen.(maybe menu will be at 0,0 en level for a small amount of time at 200,0)
	//slowly translate all tiles until they are close enough to the next the next limits (m_LvHeight * (m_CurrentLevel - 1))
	//whenever limit is reached we also add the current translation to all collisionboxes.

	// we add the currenttranslation everytime and check with limit
}

void LevelObserver::UpgradeLevel()
{
	m_CurrentLevel++;
	m_pPlayerCollisionComp->SetActive(false);
	m_HasLevelChanged = true;
	//here we set the collisioncomponent of the player to not active

	//once limit is reached this goes back to active
}

void LevelObserver::RegisterPlayer(std::shared_ptr<dae::GameObject> pPlayerObject)
{
	auto pCollisionComp = pPlayerObject->GetComponent(ComponentType::COLLISIONCOMPONENT);
	m_pPlayerCollisionComp = std::dynamic_pointer_cast<comps::CollisionComponent>(pCollisionComp);
}

void LevelObserver::RegisterLevelData(std::list<std::shared_ptr<dae::GameObject>> pPngTiles)
{
	PngTiles = pPngTiles;
}

void LevelObserver::MoveTilemap(float2 translation)
{
	for (std::shared_ptr<dae::GameObject> tile : PngTiles)
	{
		auto position = tile->GetTransform()->GetPosition();
		tile->GetTransform()->Translate({ position.x + translation.x + position.y + translation.y });
	}

	/*for (std::shared_ptr<rectangle_> collisionTile : m_CollisionWalls1)
	{
		collisionTile->posX += translation.x;
		collisionTile->posY += translation.y;
	}
	for (std::shared_ptr<rectangle_> collisionTile : m_CollisionWalls2)
	{
		collisionTile->posX += translation.x;
		collisionTile->posY += translation.y;
	}
	for (std::shared_ptr<rectangle_> collisionTile : m_CollisionWalls3)
	{
		collisionTile->posX += translation.x;
		collisionTile->posY += translation.y;
	}
	for (std::shared_ptr<rectangle_> collisionTile : m_CollisionPlatforms1)
	{
		collisionTile->posX += translation.x;
		collisionTile->posY += translation.y;
	}
	for (std::shared_ptr<rectangle_> collisionTile : m_CollisionPlatforms2)
	{
		collisionTile->posX += translation.x;
		collisionTile->posY += translation.y;
	}
	for (std::shared_ptr<rectangle_> collisionTile : m_CollisionPlatforms3)
	{
		collisionTile->posX += translation.x;
		collisionTile->posY += translation.y;
	}*/

}