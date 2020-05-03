#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent()
	:m_Position{0,0}
	,m_Rotation{0,0}
	,m_Scale{1,1}
	,m_Speed{0}
{
}

void TransformComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
	
}

void TransformComponent::Update(const dae::Scene & scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
}

void TransformComponent::Render(const dae::Scene & scene, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);
}

void TransformComponent::Translate(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void TransformComponent::Translate(float2 position)
{
	Translate(position.x, position.y);
}

void TransformComponent::Rotate(float x, float y)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
}

void TransformComponent::Rotate(float2 rotation)
{
	Rotate(rotation.x, rotation.y);
}

void TransformComponent::Scale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void TransformComponent::Scale(float2 position)
{
	Scale(position.x, position.y);
}

void TransformComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}
