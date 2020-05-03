#pragma once
#include "Entity.h"
namespace dae
{
	class Scene;
}

class FPSCounter : public Entity
{
public:
	FPSCounter(std::shared_ptr<dae::Scene> scene);
	void CreateComponents() override;
};
