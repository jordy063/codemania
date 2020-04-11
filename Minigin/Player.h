#pragma once
#include "Entity.h"
#include "TileMapLoader.h"

class Player : public Entity
{
public:
	Player(int controllerId, std::shared_ptr<dae::Scene> scene);
	void CreateComponents(int controllerId, std::shared_ptr<dae::Scene> scene);
};

