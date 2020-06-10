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
	m_PlayerDefaultPos[0] = { 50,500 };
	m_PlayerDefaultPos[1] = { 500,500 };
}

void LevelManager::Update(float elapsedSecs)
{
	
	if (m_TransisionProgress < m_CurrentLevel)
	{
		
			//we don't want to scroll too far,m_Currentlv is our max
			m_TransisionProgress += min(elapsedSecs * m_TransitionSpeed.y / m_LevelHeight, m_CurrentLevel);
			m_Translation.y = m_TransisionProgress * m_LevelHeight;

			if (m_PlayerLocationSet == false)
			{
				for (int i{}; i < m_PlayerAmount; ++i)
				{
					m_DistancePerSec[i] = CalculateAngle(i);
				}
				m_PlayerLocationSet = true;
			}
			
			//int i = 1;
			
			for (int i{}; i < m_PlayerAmount; ++i)
			{

				//we move player allong x-axis
				if (std::abs(m_PlayerTranslation[i].x - m_DistancePerSec[i].x) < 0.1f)
				{
					//destination reached

				}
				else
				{

					m_pPlayerTransforms[i]->Translate(m_CurrentPlayerPos[i].x + m_PlayerTranslation[i].x, m_PlayerTranslation[i].y + m_CurrentPlayerPos[i].y);
					m_PlayerTranslation[i].x += elapsedSecs * m_DistancePerSec[i].x / m_PlayerTranlateTime.x;
				}

				//we move player allong y-axis
				if (m_pPlayerTransforms[i]->GetPosition().y > m_Translation.y + m_PlayerDefaultPos[i].y || m_IsLocationYReached)
				{

					//destination reached
					m_pPlayerTransforms[i]->Translate(m_CurrentPlayerPos[i].x + m_PlayerTranslation[i].x, m_Translation.y + m_PlayerDefaultPos[i].y);
					m_IsLocationYReached = true;

				}
				else
				{

					m_pPlayerTransforms[i]->Translate(m_CurrentPlayerPos[i].x + m_PlayerTranslation[i].x, m_PlayerTranslation[i].y + m_CurrentPlayerPos[i].y);
					m_PlayerTranslation[i].y += elapsedSecs * m_DistancePerSec[i].y / m_PlayerTranlateTime.y;
				}
				IsCollisionSet = false;
			}

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
				for(int i{}; i < m_PlayerAmount; ++i)
					m_pPlayerCollisions[i]->SetCollision(tileMap->GetCollisionWalls(), tileMap->GetCollisionPlatforms());


				IsCollisionSet = true;

			}

			m_IsLocationYReached = false;
			m_PlayerLocationSet = false;

			for (int i{}; i < m_PlayerAmount; ++i)
			{
				UpdateIfBelowLevel(m_pPlayerTransforms[i]);
				UpdateIfAboveLevel(m_pPlayerTransforms[i]);
			}

		}
	

}

void LevelManager::UpgradeLevel()
{
	m_CurrentLevel++;
	m_ShouldUpdate = true;
	IsCollisionSet = false;
	m_PlayerTranslation[0] = {};
	m_PlayerTranslation[1] = {};
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

float2 LevelManager::CalculateAngle(int index)
{
	
	m_CurrentPlayerPos[index] = m_pPlayerTransforms[index]->GetPosition();
	

	auto distanceX = m_PlayerDefaultPos[index].x - m_CurrentPlayerPos[index].x;
	auto distanceY = m_PlayerDefaultPos[index].y + (m_CurrentLevel - 1) * m_LevelHeight - m_CurrentPlayerPos[index].y + m_PlayerCatchupDifference;

	auto distancePerSec = float2{ distanceX,distanceY };

	//transform of player +/- speed
	//if playerTransform.x < 50 do +
	//else do -


	return distancePerSec;
}
void LevelManager::ResetPlayerPos(int index)
{
	UNREFERENCED_PARAMETER(index);
	m_pPlayerTransforms[index]->Translate(m_PlayerDefaultPos[index].x, m_PlayerDefaultPos[index].y + m_CurrentLevel*m_LevelHeight);
	
}

void LevelManager::SetAmountOfPlayers(int i)
{
	m_PlayerAmount = i;
}

