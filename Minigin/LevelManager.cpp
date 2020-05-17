#include "MiniginPCH.h"
#include "LevelManager.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "TileMapLoader.h"


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
		//if (m_pPlayerTransformLeft->GetPosition().x > 50 )
		//{
		//	//translation = negative
		//	m_HorintalProgress -= elapsedSecs * m_TransitionSpeed.x;
		//	
		//}
		//else if (m_pPlayerTransformLeft->GetPosition().x > 50)
		//{
		//	//translation = negative
		//	m_HorintalProgress -= elapsedSecs * m_TransitionSpeed.x;
		//}
		//m_Translation.x = m_HorintalProgress;
		////x is fine but player should go in the direct of (50,300) with a certain speed.
		////that speed = speed*m_LevelHeight/(m_Levelheight+ m_Levelheight-characterpos) -> the difference
		//m_pPlayerTransformLeft->Translate(m_Translation.x + 50, m_Translation.y + 300);


		

		if (std::abs(m_PlayerTranslation.x - m_DistancePerSec.x) < 0.1f)
		{
			//destination reached
		
		}
		else
		{
			m_PlayerTranslation.x += elapsedSecs * m_DistancePerSec.x / m_PlayerTranlateTime;
			m_pPlayerTransformLeft->Translate(m_CurrentPlayerPos.x + m_PlayerTranslation.x, m_PlayerTranslation.y + m_CurrentPlayerPos.y);
		}
		
		if (m_pPlayerTransformLeft->GetPosition().y > m_Translation.y + m_PlayerDefaultPos.y || m_IsLocationYReached)
		{
			
			//destination reached
			m_pPlayerTransformLeft->Translate(m_CurrentPlayerPos.x + m_PlayerTranslation.x, m_Translation.y + m_PlayerDefaultPos.y);
			m_IsLocationYReached = true;

		}
		else
		{
			m_PlayerTranslation.y += elapsedSecs * m_DistancePerSec.y / m_PlayerTranlateTime;
			m_pPlayerTransformLeft->Translate(m_CurrentPlayerPos.x + m_PlayerTranslation.x, m_PlayerTranslation.y + m_CurrentPlayerPos.y);
		}
		IsCollisionSet = false;
		
	}
	else
	{
		//if a bool is false, set it to true. if we update lv that bool is false
		if (IsCollisionSet == false)
		{
			//upgrade collision
			auto tileMap = dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap();
			tileMap->UpdateLevel(m_CurrentLevel);
			
			m_pPlayerCollisionLeft->SetCollision(tileMap->GetCollisionWalls(), tileMap->GetCollisionPlatforms());
			IsCollisionSet = true;
		}

		m_IsLocationYReached = false;
		m_PlayerLocationSet = false;
	}


}

void LevelManager::UpgradeLevel()
{
	m_CurrentLevel++;
}

void LevelManager::RegisterTransformCompLeft(std::shared_ptr<TransformComponent> pPlayerTransformCompLeft, std::shared_ptr<comps::CollisionComponent> pPlayerCollisionCompLeft)
{
	m_pPlayerTransformLeft = pPlayerTransformCompLeft;
	m_pPlayerCollisionLeft = pPlayerCollisionCompLeft;
}

void LevelManager::RegisterTransformCompRight(std::shared_ptr<TransformComponent> pPlayerTransformCompRight, std::shared_ptr<comps::CollisionComponent> pPlayerCollisionCompRight)
{
	m_pPlayerTransformRight = pPlayerTransformCompRight;
	m_pPlayerCollisionRight = pPlayerCollisionCompRight;
}

float2 LevelManager::CalculateAngle()
{
	
	m_CurrentPlayerPos = m_pPlayerTransformLeft->GetPosition();
	

	auto distanceX =  m_PlayerDefaultPos.x - m_CurrentPlayerPos.x;
	auto distanceY = m_PlayerDefaultPos.y - m_CurrentPlayerPos.y;

	auto distancePerSec = float2{ distanceX,distanceY };

	//transform of player +/- speed
	//if playerTransform.x < 50 do +
	//else do -


	return distancePerSec;
}
