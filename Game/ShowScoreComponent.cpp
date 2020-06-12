#include "MiniginPCH.h"
#include "ShowScoreComponent.h"
#include "ScoreBoard.h"
void comps::ShowScoreComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	m_AllowScrolling = false;
}

void comps::ShowScoreComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);
	int score{ ScoreBoard::GetInstance().GetScore() };

	//we only update the score if the score is changed
	if (m_Score != score)
	{
		SetText("Score: " + std::to_string(score));
	}

	TextComponent::Update(scene, elapsedSecs, pos);
}