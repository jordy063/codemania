#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
namespace comps
{
	class HealthComponent;
	class BoundingBoxComponent;
}
namespace comps
{
	class PlayerVersusComponent final : public comps::BaseComponent
	{
	public:
		PlayerVersusComponent(std::shared_ptr<dae::GameObject> pPlayer1, std::shared_ptr < comps::BoundingBoxComponent> pEnemyPlayerBoundingBox,
			std::shared_ptr < comps::HealthComponent> pEnemyPlayerHealthComp);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:
		std::vector < std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;
		std::vector<std::shared_ptr<comps::BoundingBoxComponent>> m_pPlayerBoundingBoxes;
	};
}

