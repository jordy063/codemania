#pragma once
#include "BaseComponent.h"
namespace comps
{
	class HealthComponent final : public comps::BaseComponent
	{
	public:
		HealthComponent(int health, int id);
		~HealthComponent() = default;;
		int GetHealth() const { return m_Health; };
		void DropHealth(int amount);
		void ResetHealth();
		bool GetIsInvinsible() const { return m_IsInvisble; }
		void SetIsTransitioning();
	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		int m_Health;
		int m_StartHealth;
		bool m_IsInvisble = true;
		float m_InvinsibleTime;
		float m_InvinsibleTimer;
		bool m_IsTransisioning = false;
		float m_TransitionTimer;
		float m_TransitionTime;
		int m_Id;
	};
}
