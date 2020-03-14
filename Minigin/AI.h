#pragma once
#include "Entity.h"

class AI : public Entity
{
public:
	AI();
	void CreateComponents() override;
	void Update(float elapsedSecs) override;
};
