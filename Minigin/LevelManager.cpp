#include "MiniginPCH.h"
#include "LevelManager.h"
#include "TransformComponent.h"

void LevelManager::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void LevelManager::Update(float elapsedSecs)
{
	
	if (m_TransisionProgress < m_CurrentLevel)
	{
		//we don't want to scroll too far,m_Currentlv is our max
		m_TransisionProgress += min(elapsedSecs*m_TransitionSpeed/m_LevelHeight, m_CurrentLevel);
		m_Translation.y = m_TransisionProgress * m_LevelHeight;
		m_pPlayerTransformLeft->Translate(50, m_Translation.y + 50);
	}


}

void LevelManager::UpgradeLevel()
{
	m_CurrentLevel++;
}

void LevelManager::RegisterTransformCompLeft(std::shared_ptr<TransformComponent> pPlayerTransformCompLeft)
{
	m_pPlayerTransformLeft = pPlayerTransformCompLeft;
}

void LevelManager::RegisterTransformCompRight(std::shared_ptr<TransformComponent> pPlayerTransformCompRight)
{
	m_pPlayerTransformRight = pPlayerTransformCompRight;
}