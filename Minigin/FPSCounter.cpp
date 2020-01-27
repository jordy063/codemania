#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "FpsComponent.h"


FPSCounter::FPSCounter()
{
	CreateEntityObject();

	CreateComponents();
}

void FPSCounter::CreateComponents()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);


	auto fpsTextComp =std::shared_ptr<comps::FpsComponent>(new comps::FpsComponent("fps: ",font));


	m_EntityObject->AddComponent(fpsTextComp);
	fpsTextComp->SetAlignment(comps::HAlign::RIGHT, comps::VAlign::TOP);
	m_EntityObject->SetPosition(640, 0);

}
