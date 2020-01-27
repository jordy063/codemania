#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "Transform.h"
#include <SDL.h>
#include "Logger.h"




comps::BaseComponent::BaseComponent() :  m_IsInitialized(false) 
{

};
comps::BaseComponent::~BaseComponent()
{
	
}

void comps::BaseComponent::Render(const dae::Scene & scene, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(pos);
}

void comps::BaseComponent::RootInitialize(const dae::Scene & scene)
{
	assert(!m_IsInitialized);
	if (m_IsInitialized)
		return;

	Initialize(scene);

	m_IsInitialized = true;
}