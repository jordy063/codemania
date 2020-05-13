#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
#include <list>
#include "Singleton.h"

//IDEA
//we get a list of pngtiles
namespace comps
{
	class textureComponent;
	class CollisionComponent;
}



class LevelObserver final : public dae::Singleton<LevelObserver>
{
public:

	~LevelObserver() = default;

	void Initialize(const dae::Scene& scene);
	void Update(const dae::Scene& scene, float elapsedSecs);

	void UpgradeLevel();
	void RegisterPlayer(std::shared_ptr<dae::GameObject> pPlayerObject);
	void RegisterLevelData(std::list<std::shared_ptr<dae::GameObject>> pPngTiles);

private:
	int m_LvHeight;
	int m_CurrentLevel;
	float2 m_CurrentTranslation;
	int m_Limits[3];
	bool m_Hasmoved;
	float m_TranslationSpeed;
	bool m_HasLevelChanged = false;

	std::shared_ptr<comps::CollisionComponent> m_pPlayerCollisionComp;
	std::list<std::shared_ptr<dae::GameObject>> PngTiles;

	void MoveTilemap(float2 translation);
};
