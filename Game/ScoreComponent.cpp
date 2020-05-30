#include "MiniginPCH.h"
#include "ScoreComponent.h"

comps::ScoreComponent::ScoreComponent()
	:m_Score{}
{
}

void comps::ScoreComponent::AddScore(int score)
{
	m_Score += score;
}

void comps::ScoreComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::ScoreComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
}
