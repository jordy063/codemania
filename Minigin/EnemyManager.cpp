#include "MiniginPCH.h"
#include "EnemyManager.h"
#include "Ghost.h"
#include "Scene.h"
#include "ZenChan.h"

//should be singleton
EnemyManager::EnemyManager()
{
}

void EnemyManager::MakeEnemies(std::shared_ptr<dae::Scene> scene,int level)
{
	//OPTION 1
	//we check how how enemies we currently have and see if we need more of that type
	switch (level)
	{
	case 1:
		MakeEnemiesLevel1(scene);
		break;
	case 2:
		break;
	case 3:
		break;

	default:
		break;
	}


	//OPTION 2
	//we make all enemies and add them to the scene
	//we just create new enemies every time
}

void EnemyManager::Update(float elapsedSecs, std::shared_ptr<Player> player)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(player);
	//for all enemies update and check if an enemy hits the avatar

	for (std::shared_ptr <Enemy> enemy : m_pEnemies)
	{
		enemy->Update(elapsedSecs, player);
		
	}

}

void EnemyManager::MakeEnemiesLevel1(std::shared_ptr<dae::Scene> scene)
{
	//make a buffer, translate it and add it to list
	auto enemy = std::shared_ptr <Enemy>(new Ghost(scene, 1));
	enemy->GetGameObject()->GetTransform()->Translate(150, 100);
	m_pEnemies.push_back(enemy);

	scene->Add(enemy);
	enemy = std::shared_ptr <Enemy>(new Ghost(scene, 1));
	enemy->GetGameObject()->GetTransform()->Translate(250, 100);
	m_pEnemies.push_back(enemy);
	scene->Add(enemy);

	enemy = std::shared_ptr <Enemy>(new ZenChan(scene, 1));
	enemy->GetGameObject()->GetTransform()->Translate(200, 100);
	m_pEnemies.push_back(enemy);
	scene->Add(enemy);
}
