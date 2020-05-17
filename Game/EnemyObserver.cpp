
#include "MiniginPCH.h"
#include "EnemyObserver.h"
#include "SceneManager.h"
#include "LevelManager.h"

EnemyObserver::EnemyObserver()
	:m_EnemyCount()
{
}

EnemyObserver::~EnemyObserver()
{
}


void EnemyObserver::UpCounter()
{
	m_EnemyCount++;
}


void EnemyObserver::DownCounter()
{
	m_EnemyCount--;
	//call singleton itemmanager and make item
	if (m_EnemyCount == 0)
	{
		LevelManager::GetInstance().UpgradeLevel();
		//TODO
		//start timer
		//if timer done do level transision
	}
}
