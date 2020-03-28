#pragma once
#include "Entity.h"
#include "TileMapLoader.h"

class Player : public Entity
{
public:
	Player(const std::shared_ptr< TileMapLoader> tilemap);
	void CreateComponents(const std::shared_ptr< TileMapLoader> tilemap);
};

