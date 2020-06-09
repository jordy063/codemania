#pragma once
#include "Singleton.h"
#include "structs.h"
#include "Scene.h"

class TransformComponent;

namespace comps
{
	class CollisionComponent;
}

class LevelManager final : public dae::Singleton< LevelManager>
{
public:
	void Initialize(const dae::Scene& scene);
	void Update( float elapsedSecs);
	void UpgradeLevel();
	float GetTranslationX() const { return m_Translation.x; }
	float GetTranslationY() const { return m_Translation.y; }
	void RegisterTransformCompLeft(std::shared_ptr< TransformComponent> pTransformCompLeft,std::shared_ptr<comps::CollisionComponent> pPlayerCollisionCompLeft);
	void RegisterTransformCompRight(std::shared_ptr<TransformComponent> pTransformCompRight, std::shared_ptr<comps::CollisionComponent> pPlayerCollisionCompRight);
	int GetCurrentLevel() const { return m_CurrentLevel; }
	bool GetShouldUpdate() const { return m_ShouldUpdate; }
	void UpdateIfBelowLevel(std::shared_ptr<TransformComponent> pTranform, bool firstTime = false, float2 startPos = {});
	void UpdateIfAboveLevel(std::shared_ptr<TransformComponent> pTranform, bool firstTime = false, float2 startPos = {});
	void ResetPlayerPos(int index);
	void SetAmountOfPlayers(int i);
private:
	int m_CurrentLevel{0};
	float2 m_Translation{ 0,0 };
	float m_TransisionProgress{};
	float m_LevelHeight{ 24*25 };
	float2 m_TransitionSpeed{5,100 };
	float m_HorintalProgress{};
	float2 m_CurrentPlayerPos[2]{};
	float2 m_DistancePerSec[2];
	float2 m_PlayerTranslation[2];

	float2 m_PlayerDefaultPos[2];
	float2 m_PlayerTranlateTime{ 5,1 };

	std::shared_ptr< TransformComponent> m_pPlayerTransforms[2];
	std::shared_ptr< comps::CollisionComponent> m_pPlayerCollisions[2];

	bool m_PlayerLocationSet = false;
	bool m_IsLocationYReached = false;
	bool IsCollisionSet = true;
	bool m_ShouldUpdate = false;
	int m_PlayerAmount;
	float2 CalculateAngle(int index);

};

