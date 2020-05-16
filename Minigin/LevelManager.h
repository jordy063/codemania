#pragma once
#include "Singleton.h"
#include "structs.h"
#include "Scene.h"

class TransformComponent;


class LevelManager final : public dae::Singleton< LevelManager>
{
public:
	void Initialize(const dae::Scene& scene);
	void Update( float elapsedSecs);
	void UpgradeLevel();
	float GetTranslationX() const { return m_Translation.x; }
	float GetTranslationY() const { return m_Translation.y; }
	void RegisterTransformCompLeft(std::shared_ptr< TransformComponent> pTransformCompLeft);
	void RegisterTransformCompRight(std::shared_ptr<TransformComponent> pTransformCompRight);
private:
	int m_CurrentLevel{1};
	float2 m_Translation{ 0,0 };
	float m_TransisionProgress{};
	float m_LevelHeight{ 16*24 };
	float m_TransitionSpeed{ 20 };

	std::shared_ptr< TransformComponent> m_pPlayerTransformLeft;
	std::shared_ptr< TransformComponent> m_pPlayerTransformRight;
};

