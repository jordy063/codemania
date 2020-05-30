#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "FpsComponent.h"
#include "Scene.h"
#include <shared_mutex>


FPSCounter::FPSCounter()
{

}

void FPSCounter::Initialize()
{
	auto object = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	dae::SceneManager::GetInstance().GetActiveScene()->Add(object);

	auto fpsTextComp = std::shared_ptr<comps::FpsComponent>(new comps::FpsComponent(font, 64, 32, { 255,255,255 }));


	object->AddComponent(fpsTextComp,ComponentType::FPSCOMPONENT);
	fpsTextComp->SetAlignment(comps::HAlign::RIGHT, comps::VAlign::TOP);
	object->SetPosition(580, 0);


}
