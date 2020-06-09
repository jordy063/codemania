#pragma once
#include "Singleton.h"
#include "PhysicsComponent.h"
#include <set>

class TransformComponent;
namespace comps
{
	class BoundingBoxComponent;
	class HealthComponent;
}
class BoulderManager final : public dae::Singleton<BoulderManager>
{
public:
	void MakeBoulder(float2 pos, comps::Direction direction);
	void RemoveBoulder(std::shared_ptr <TransformComponent> pTransform);
	bool CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBoulderBoundingBox, int playerId);
	void RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers);

private:
	float m_BoulderSpeed = 50;
	std::set<std::shared_ptr<dae::GameObject>> m_pBoulders;
	std::vector<std::shared_ptr<comps::BoundingBoxComponent>> m_pPlayerBoundingBoxes;
	std::vector<std::shared_ptr<comps::HealthComponent>> m_PlayerHealthComps;
};

