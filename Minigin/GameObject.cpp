#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
	:m_IsEnabled(true)
{
	m_pScene = nullptr;
	m_pTransform = std::shared_ptr<TransformComponent>(new TransformComponent());
}

dae::GameObject::~GameObject()
{
	
	/*for (int i{}; i < m_pComponents.size(); ++i)
	{
		if (m_pComponents.at(i) != nullptr && m_pComponents.at(i) != m_pTransform )
		{
			delete m_pComponents.at(i);
		}
	}*/
	//delete m_pTransform;
	
}

void dae::GameObject::AddComponent(std::shared_ptr<comps::BaseComponent> comp,ComponentType type)
{
	m_pComponents[type] = comp;
	//m_pComponents.push_back(comp);
	m_Types.push_back(type);
}

void dae::GameObject::ChangeScene(Scene * newScene)
{
	if (m_pScene == nullptr)
	{
		m_pScene = newScene;
	}
}

void dae::GameObject::Clear()
{
	m_pComponents.clear();
	m_Types.clear();
	//m_pComponents.push_back(m_pTransform);
}

void dae::GameObject::Disable()
{
	m_IsEnabled = false;
}

void dae::GameObject::Enable()
{
	m_IsEnabled = true;
}

void dae::GameObject::Initialize()
{
	AddComponent(m_pTransform,ComponentType::TRANSFORMCOMP);
	for (ComponentType type : m_Types)
	{
		m_pComponents[type]->RootInitialize(*m_pScene);
	}

	/*for (std::shared_ptr<comps::BaseComponent> comp : m_pComponents)
	{
		comp->RootInitialize(*m_pScene);
	}*/
}

void dae::GameObject::RegisterTileMap(std::shared_ptr<TileMapLoader> tileMapLoader)
{
	m_pTileMap = tileMapLoader;
}

void dae::GameObject::Update(float elapsedSecs)
{
	if (m_IsEnabled)
	{
		for (ComponentType type : m_Types)
		{
			m_pComponents[type]->Update(*m_pScene, elapsedSecs, m_pTransform->GetPosition());
		}
	}
	/*for (std::shared_ptr<comps::BaseComponent> comp : m_pComponents)
	{
		comp->Update(*m_pScene, elapsedSecs, m_pTransform->GetPosition());
	}*/
}

void dae::GameObject::Render() 
{
	if (m_IsEnabled)
	{
		for (ComponentType type : m_Types)
		{
			if(m_pComponents[type] != nullptr)
			m_pComponents[type]->Render(*m_pScene, m_pTransform->GetPosition());
		}
	}
	/*for (std::shared_ptr<comps::BaseComponent> comp : m_pComponents)
	{
		comp->Render(*m_pScene, m_pTransform->GetPosition());
	}*/

}

void dae::GameObject::SetPosition(float x, float y)
{
	
	m_pTransform->Translate(x,y);
}
void dae::GameObject::SetScale(float x, float y)
{

	m_pTransform->Scale(x, y);
}
