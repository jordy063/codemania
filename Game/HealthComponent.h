#pragma once
#include "BaseComponent.h"
namespace comps
{
	class HealthComponent final : public comps::BaseComponent
	{
	public:
		HealthComponent(int health);
		void DropHealth(int amount);
		void ResetHealth();
	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		int m_Health;
		int m_StartHealth;
	};
}
