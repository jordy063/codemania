#pragma once
#include "Singleton.h"
#include "structs.h"
#include <set>

namespace comps
{
	class PhysicsComponent;
}
namespace dae
{
	class GameObject;
}
class TransformComponent;
class ScorePopUpManager final: public dae::Singleton< ScorePopUpManager>
{
public:
	void MakeScorePopUp(ItemType itemType, int spriteId, float2 position);
	void RemoveScorePopUp(std::shared_ptr <TransformComponent> pTransform);

private:
	std::set<std::shared_ptr<dae::GameObject>> m_pScoreObjects;
};

