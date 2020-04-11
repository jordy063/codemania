#pragma once
#include "Entity.h"
#include "TileMapLoader.h"


class AI : public Entity
{
public:
	AI(std::shared_ptr<dae::Scene> scene);
	void CreateComponents(std::shared_ptr<dae::Scene> scene);
	void ClearAI();

private:

};
