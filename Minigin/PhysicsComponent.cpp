#include "MiniginPCH.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void PhysicsComponent::Update(const dae::Scene & scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
}
