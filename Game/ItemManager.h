#pragma once
#include "Singleton.h"
#include "structs.h"
#include <vector>
class ItemManager final : public dae::Singleton< ItemManager>
{
public:
	void makeItem(float2 pos);


private:
	//not sure if I need a private vector yet
};

