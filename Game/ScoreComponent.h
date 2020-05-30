#pragma once
class ScoreComponent
{
};

#pragma once
#include "BaseComponent.h"
namespace comps
{
	class ScoreComponent final : public comps::BaseComponent
	{
	public:
		ScoreComponent();
		~ScoreComponent() = default;;
		void AddScore(int score);
	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		int m_Score;
	};
}