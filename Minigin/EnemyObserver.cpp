#include "MiniginPCH.h"
#include "EnemyObserver.h"
#include "SceneManager.h"

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

	if (m_EnemyCount == 0)
	{
		//TODO
	}
}
