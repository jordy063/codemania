#include "MiniginPCH.h"
#include "LevelManager.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "TileMapLoader.h"
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
		m_TransisionProgress += min(elapsedSecs*m_TransitionSpeed.y/m_LevelHeight, m_CurrentLevel);
		m_Translation.y = m_TransisionProgress * m_LevelHeight;

		if (m_PlayerLocationSet == false)
		{
			m_DistancePerSec = CalculateAngle();
			m_PlayerLocationSet = true;
		}
		

		//we move player allong x-axis
		if (std::abs(m_PlayerTranslation.x - m_DistancePerSec.x) < 0.1f)
		{
			//destination reached
		
		}
		else
		{
			
			m_pPlayerTransforms[0]->Translate(m_CurrentPlayerPos.x + m_PlayerTranslation.x, m_PlayerTranslation.y + m_CurrentPlayerPos.y);
			m_PlayerTranslation.x += elapsedSecs * m_DistancePerSec.x / m_PlayerTranlateTime.x;
		}

		//we move player allong y-axis
		if (m_pPlayerTransforms[0]->GetPosition().y > m_Translation.y + m_PlayerDefaultPos.y || m_IsLocationYReached)
		{
			
			//destination reached
			m_pPlayerTransforms[0]->Translate(m_CurrentPlayerPos.x + m_PlayerTranslation.x, m_Translation.y + m_PlayerDefaultPos.y);
			m_IsLocationYReached = true;

		}
		else
		{
			
			m_pPlayerTransforms[0]->Translate(m_CurrentPlayerPos.x + m_PlayerTranslation.x, m_PlayerTranslation.y + m_CurrentPlayerPos.y);
			m_PlayerTranslation.y += elapsedSecs * m_DistancePerSec.y / m_PlayerTranlateTime.y;
		}
		IsCollisionSet = false;
		
	}
	else
	{
		//if a bool is false, set it to true. if we update lv that bool is false
		m_ShouldUpdate = false;
		if (IsCollisionSet == false)
		{
			//upgrade collision
			auto tileMap = dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap();
			tileMap->UpdateLevel(m_CurrentLevel);
			
			m_pPlayerCollisions[0]->SetCollision(tileMap->GetCollisionWalls(), tileMap->GetCollisionPlatforms());
			
			IsCollisionSet = true;
			
		}

		m_IsLocationYReached = false;
		m_PlayerLocationSet = false;

		
		UpdateIfBelowLevel(m_pPlayerTransforms[0]);
		UpdateIfAboveLevel(m_pPlayerTransforms[0]);
	}


}

void LevelManager::UpgradeLevel()
{
	m_CurrentLevel++;
	m_ShouldUpdate = true;
	IsCollisionSet = false;
	m_PlayerTranslation = {};
}


void LevelManager::RegisterTransformCompLeft(std::shared_ptr<TransformComponent> pPlayerTransformCompLeft, std::shared_ptr<comps::CollisionComponent> pPlayerCollisionCompLeft)
{
	m_pPlayerTransforms[0] = pPlayerTransformCompLeft;

	m_pPlayerCollisions[0] = pPlayerCollisionCompLeft;
}

void LevelManager::RegisterTransformCompRight(std::shared_ptr<TransformComponent> pPlayerTransformCompRight, std::shared_ptr<comps::CollisionComponent> pPlayerCollisionCompRight)
{
	m_pPlayerTransforms[1] = pPlayerTransformCompRight;
	m_pPlayerCollisions[1] = pPlayerCollisionCompRight;
}


void LevelManager::UpdateIfBelowLevel(std::shared_ptr<TransformComponent> pTranform, bool firstTime,float2 startPos)
{
	if(m_TransisionProgress >= m_CurrentLevel)
	if (pTranform->GetPosition().y > 600 + m_Translation.y)
	{
		if(firstTime)
			pTranform->Translate(startPos.x, startPos.x);
		else
		pTranform->Translate(pTranform->GetPosition().x, m_Translation.y + 15);
	}
}

void LevelManager::UpdateIfAboveLevel(std::shared_ptr<TransformComponent> pTranform, bool firstTime, float2 startPos)
{
	if (m_TransisionProgress >= m_CurrentLevel)
	if (pTranform->GetPosition().y < m_Translation.y)
	{
		if (firstTime)
			pTranform->Translate(startPos.x, startPos.x);
		else
		pTranform->Translate(pTranform->GetPosition().x, m_Translation.y + 600);
	}
}

float2 LevelManager::CalculateAngle()
{
	
	m_CurrentPlayerPos = m_pPlayerTransforms[0]->GetPosition();
	

	auto distanceX =  m_PlayerDefaultPos.x - m_CurrentPlayerPos.x;
	auto distanceY = m_PlayerDefaultPos.y + (m_CurrentLevel - 1) * m_LevelHeight - m_CurrentPlayerPos.y;

	auto distancePerSec = float2{ distanceX,distanceY };

	//transform of player +/- speed
	//if playerTransform.x < 50 do +
	//else do -


	return distancePerSec;
}
void LevelManager::ResetPlayerPos(int index)
{
	UNREFERENCED_PARAMETER(index);
	m_pPlayerTransforms[0]->Translate(m_PlayerDefaultPos);
	
}

