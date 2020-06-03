#pragma once
#include "Singleton.h"
#include "structs.h"
#include <list>

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
	std::list<std::shared_ptr<dae::GameObject>> m_pScoreObjects;
};

