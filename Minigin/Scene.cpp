#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "FpsComponent.h"



unsigned int dae::Scene::idCounter = 0;

bool dae::Scene::CreateFPSCounter()
{
	m_pFPSCounter = std::shared_ptr<FPSCounter>(new FPSCounter());

	

	if (m_pFPSCounter != nullptr)
	{
		
		Add(m_pFPSCounter);
		
		return true;
	}
	PrintColor(TextColor::RED, "cannot create fps counter!");
	return false;
}

dae::Scene::Scene(const std::string name) : mName(name) {}

dae::Scene::~Scene()
{
	for (unsigned int i{}; i < mObjects.size(); ++i)
	{
		if (mObjects.at(i) != nullptr )
		{
			//delete mObjects.at(i);
		}
	}
}

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	mObjects.push_back(object);
	
}
void  dae::Scene::Add(const std::shared_ptr<Entity>& object)
{
	mObjects.push_back(object->GetGameObject());
}

void dae::Scene::AddGameObject(const std::shared_ptr<GameObject>& object)
{
	Add(object);
	object->ChangeScene(this);
}

void dae::Scene::Initialize()
{
	m_Lag = 1;
	m_Frames = 0;

	CreateFPSCounter();
	for (auto gameObject : mObjects)
	{
		if (gameObject != nullptr)
		{
			gameObject->Initialize();
		}
	}
}

void dae::Scene::Update(float elapsedSecs)
{
	m_Lag += elapsedSecs;
	m_Frames++;

	/*if (m_Lag >= 1)
	{
		
		m_pFpsTextComp->SetText("fps: " + std::to_string(int(m_Frames)));
		m_Frames = 0;
		m_Lag -= 1;
	}*/

	for(auto gameObject : mObjects)

	{
		if (gameObject != nullptr)
		{
			gameObject->Update(elapsedSecs);
		}
	}

	
}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		
		gameObject->Render();
	}
}

