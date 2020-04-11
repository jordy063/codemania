#pragma once
#include"Entity.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
}

class EnemyObserver final : public dae::Singleton<EnemyObserver>
{
public:

	EnemyObserver();
	~EnemyObserver();

	void UpCounter();
	void DownCounter();

private:
	int m_EnemyCount;
	std::shared_ptr<dae::Scene> m_pScene;

};

