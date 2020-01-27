#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
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

void dae::GameObject::AddComponent(std::shared_ptr<comps::BaseComponent> comp)
{
	m_pComponents.push_back(comp);
	
}

void dae::GameObject::ChangeScene(Scene * newScene)
{
	if (m_pScene == nullptr)
	{
		m_pScene = newScene;
	}
}

void dae::GameObject::Initialize()
{
	AddComponent(m_pTransform);
	for (std::shared_ptr<comps::BaseComponent> comp : m_pComponents)
	{
		comp->RootInitialize(*m_pScene);
	}
}

void dae::GameObject::Update(float elapsedSecs)
{
	for (std::shared_ptr<comps::BaseComponent> comp : m_pComponents)
	{
		comp->Update(*m_pScene, elapsedSecs, m_pTransform->GetPosition());
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<comps::BaseComponent> comp : m_pComponents)
	{
		comp->Render(*m_pScene, m_pTransform->GetPosition());
	}

}

void dae::GameObject::SetPosition(float x, float y)
{
	
	m_pTransform->Translate(x,y);
}
void dae::GameObject::SetScale(float x, float y)
{

	m_pTransform->Scale(x, y);
}
