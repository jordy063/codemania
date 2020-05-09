#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include <list>

//IDEA
//we get a list of pngtiles
namespace comps
{
	class textureComponent;
}

namespace comps
{

	class LevelTranslater final :public comps::BaseComponent
	{
	public:

		LevelTranslater(std::list<std::shared_ptr<comps::textureComponent>> pngList, std::list<std::shared_ptr<rectangle_>> collisionList);
		~LevelTranslater();

		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

		void UpgradeLevel();

	private:
		int m_LvHeight;
		int m_CurrentLevel;
		int m_CurrentTranslation;
	};
}