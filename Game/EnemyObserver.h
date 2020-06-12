#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class GameObject;
}
namespace comps
{
	class HealthComponent;
}

class EnemyObserver final : public dae::Singleton<EnemyObserver>
{
public:

	EnemyObserver();
	~EnemyObserver();
	void RegistersPlayerHealthComps(std::vector<std::shared_ptr<dae::GameObject>> pPlayers);
	void UpCounter();
	void DownCounter();
	void Reset();
private:
	int m_EnemyCount;
	std::vector<std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;

};

