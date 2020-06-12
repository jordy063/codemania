#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "SceneObject.h"
#include <SDL.h>
#include "Logger.h"
#include <assert.h>




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
	if (m_IsInitialized)
		return;
	assert(!m_IsInitialized);

	Initialize(scene);

	m_IsInitialized = true;
}