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

void comps::BaseComponent::RootInitialize(const dae::Scene & scene)
{
	assert(!m_IsInitialized);
	if (m_IsInitialized)
		return;

	Initialize(scene);

	m_IsInitialized = true;
}