#include "MiniginPCH.h"
#include "LevelTranslaterComponent.h"

comps::LevelTranslater::LevelTranslater(std::list<std::shared_ptr<comps::textureComponent>> pngList, std::list<std::shared_ptr<rectangle_>> collisionList)
	:m_CurrentLevel(0)
{
}

comps::LevelTranslater::~LevelTranslater()
{
}

void comps::LevelTranslater::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	//we place the default pos somewhere far away
	//this will update everytime
	m_LvHeight = 256;
}

void comps::LevelTranslater::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	//if needed the first time the currentlevel is 1 we translate the lv somewhere above the screen.(maybe menu will be at 0,0 en level for a small amount of time at 200,0)
	//slowly translate all tiles until they are close enough to the next the next limits (m_LvHeight * (m_CurrentLevel - 1))
	//whenever limit is reached we also add the current translation to all collisionboxes.

	// we add the currenttranslation everytime and check with limit
}

void comps::LevelTranslater::UpgradeLevel()
{
	m_CurrentLevel++;
}
