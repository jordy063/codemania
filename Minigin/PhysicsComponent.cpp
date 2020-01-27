#include "MiniginPCH.h"
#include "PhysicsComponent.h"



comps::PhysicsComponent::PhysicsComponent(std::shared_ptr<TransformComponent> transform)
	:m_Velocity{0,0}
	, m_Transform{transform}
{

	DirToVec[Direction::LEFT] = float2{ -1,0 };
	DirToVec[Direction::RIGHT] = float2{ 1,0 };
	DirToVec[Direction::UP] = float2{ 0,1 };
	DirToVec[Direction::DOWN] = float2{ 0,-1 };
}


comps::PhysicsComponent::~PhysicsComponent()
{
}

void comps::PhysicsComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::PhysicsComponent::Update(const dae::Scene & scene, float elapsedSecs, float2 pos)
{
	Move(elapsedSecs);
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
}
void comps::PhysicsComponent::Move(float elapsedSecs)
{
	float2 CurrentPosition = m_Transform->GetPosition();
	CurrentPosition.x += elapsedSecs * m_Velocity.x;
	CurrentPosition.y += elapsedSecs * m_Velocity.y;

	m_Transform->Translate(CurrentPosition);
}
void comps::PhysicsComponent::SetVelocity(float2 velocity)
{
	m_Velocity = velocity;
}
void comps::PhysicsComponent::SetDirection(float2 direction)
{
	float factor = sqrt(pow(m_Velocity.x, 2) + pow(m_Velocity.y, 2)) / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	m_Velocity.x = direction.x*factor;
	m_Velocity.y = direction.y*factor;
}
void comps::PhysicsComponent::SetDirection(Direction direction)
{
	SetDirection(DirToVec[direction]);
}
void comps::PhysicsComponent::SetSpeed(float speed)
{
	float factor = speed / sqrt(pow(m_Velocity.x, 2) + pow(m_Velocity.y, 2));
	m_Velocity.x *= factor;
	m_Velocity.y *= factor;
}
void comps::PhysicsComponent::SetMovement(float2 direction, float speed)
{
	SetVelocity(direction);
	SetSpeed(speed);
}

void comps::PhysicsComponent::SetMovement(Direction direction, float speed)
{
	SetMovement(DirToVec[direction], speed);
}
