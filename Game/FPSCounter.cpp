#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "FpsComponent.h"
#include "Scene.h"


FPSCounter::FPSCounter(std::shared_ptr<dae::Scene> scene)
{
	CreateEntityObject();
	scene->Add(m_EntityObject);
	CreateComponents();
}

void FPSCounter::CreateComponents()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);


	auto fpsTextComp =std::shared_ptr<comps::FpsComponent>(new comps::FpsComponent("fps: ",font,85,40));


	m_EntityObject->AddComponent(fpsTextComp);
	fpsTextComp->SetAlignment(comps::HAlign::RIGHT, comps::VAlign::TOP);
	m_EntityObject->SetPosition(600, 0);

}
