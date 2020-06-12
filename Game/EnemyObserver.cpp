
#include "MiniginPCH.h"
#include "EnemyObserver.h"
#include "SceneManager.h"
#include "LevelManager.h"
#include "EnemyManager.h"
#include "SoundManager2.h"
#include "HealthComponent.h"
#include "GameObject.h"


EnemyObserver::EnemyObserver()
	:m_EnemyCount()
{
}

EnemyObserver::~EnemyObserver()
{
}

void EnemyObserver::RegistersPlayerHealthComps(std::vector<std::shared_ptr<dae::GameObject>> pPlayers)
{
	for (std::shared_ptr<dae::GameObject> pPlayer : pPlayers)
	{
		auto healthComp = pPlayer->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));
	}
}


void EnemyObserver::UpCounter()
{
	m_EnemyCount++;
}


void EnemyObserver::DownCounter()
{
	m_EnemyCount--;
	if (m_EnemyCount == 0)
	{
		std::string filename{ "../Sounds/levelCleared.wav" };
		SoundManager2::GetInstance().playEffect(filename);
		LevelManager::GetInstance().UpgradeLevel();
		
		//if the levelmanager is done. after that we spawn our enemies
		
		EnemyManager::GetInstance().MakeEnemies(dae::SceneManager::GetInstance().GetActiveScene(), LevelManager::GetInstance().GetCurrentLevel());
		
		//here we add invisibility to the player for a small amount of time
		for (std::shared_ptr<comps::HealthComponent> pHealthComp : m_pPlayerHealthComps)
		{
			pHealthComp->SetIsTransitioning();
		}
	}
}

void EnemyObserver::Reset()
{
	m_pPlayerHealthComps.clear();
	m_EnemyCount = 0;
}
