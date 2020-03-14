#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(float elapsedSecs)
{
	for(auto scene : mScenes)
	{
		scene->Update(elapsedSecs);
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	m_ActiveScene = mScenes.size() - 1;
	return *scene;
}
