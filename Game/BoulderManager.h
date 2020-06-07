#pragma once
#include "Singleton.h"
#include "PhysicsComponent.h"
#include <set>

class TransformComponent;
class BoulderManager final : public dae::Singleton<BoulderManager>
{
public:
	void MakeBoulder(std::shared_ptr<TransformComponent> transform, comps::Direction direction);
	void CheckIfHit();
	void RemoveBoulder(std::shared_ptr <TransformComponent> pTransform);

private:
	float m_BoulderSpeed = 50;
	std::set<std::shared_ptr<dae::GameObject>> m_pBoulders;
};

