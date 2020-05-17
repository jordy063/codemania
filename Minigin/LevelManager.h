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
private:
	int m_CurrentLevel{0};
	float2 m_Translation{ 0,0 };
	float m_TransisionProgress{};
	float m_LevelHeight{ 16*24 };
	float2 m_TransitionSpeed{5,20 };
	float m_HorintalProgress{};
	float2 m_CurrentPlayerPos{};
	float2 m_DistancePerSec{};
	float2 m_PlayerTranslation{};

	float2 m_PlayerDefaultPos{50,300};
	float m_PlayerTranlateTime{ 5 };

	std::shared_ptr< TransformComponent> m_pPlayerTransformLeft;
	std::shared_ptr< comps::CollisionComponent> m_pPlayerCollisionLeft;
	std::shared_ptr< TransformComponent> m_pPlayerTransformRight;
	std::shared_ptr< comps::CollisionComponent> m_pPlayerCollisionRight;
	bool m_PlayerLocationSet = false;
	bool m_IsLocationYReached = false;
	bool IsCollisionSet = true;

	float2 CalculateAngle();
};

