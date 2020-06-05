#pragma once
#include "Singleton.h"
class TransformComponent;
class BoulderManager final : public dae::Singleton<BoulderManager>
{
public:
	void MakeBoulder(std::shared_ptr<TransformComponent> transform);
	void CheckIfHit();
};

