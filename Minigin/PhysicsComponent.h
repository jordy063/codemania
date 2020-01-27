#pragma once
#include "BaseComponent.h"
class PhysicsComponent : public comps::BaseComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

protected:
	virtual void Initialize(const dae::Scene& scene) override;
	virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

private: 
	float2 m_Velocity;
};

