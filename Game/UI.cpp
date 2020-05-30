#include "MiniginPCH.h"
#include "UI.h"
#include "GameObject.h"
#include <shared_mutex>
#include "TextureComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Font.h"

UI::UI()
	:m_FileName{ "../Graphics/UIBar.png" }
{
	
}

void UI::Initialize()
{

	//UI BAR
	auto topUIBar = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	dae::SceneManager::GetInstance().GetActiveScene()->Add(topUIBar);

	auto textureComp = std::shared_ptr<comps::TextureComponent>(new comps::TextureComponent(m_FileName,600, 30,false));
	topUIBar->AddComponent(textureComp, ComponentType::TEXTURECOMPONENT);
	
	textureComp->SetAlignment(comps::HAlign::LEFT, comps::VAlign::TOP);
	topUIBar->GetTransform()->Translate(0, 0);


	//SCORE PLAYER 1
	auto score1Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	dae::SceneManager::GetInstance().GetActiveScene()->Add(score1Object);

	auto score1TextComp = std::shared_ptr<comps::TextComponent>(new comps::TextComponent( font, 64, 28, { 0,255,0 }));
	score1TextComp->SetText("Score: ");

	score1Object->AddComponent(score1TextComp, ComponentType::TEXTCOMPONENT);
	score1Object->SetPosition(20, 5);

	//health PLAYER 1
	auto health1Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(health1Object);

	auto health1TextComp = std::shared_ptr<comps::TextComponent>(new comps::TextComponent(font, 64, 28, { 0,255,0 }));
	health1TextComp->SetText("health: ");

	health1Object->AddComponent(health1TextComp, ComponentType::TEXTCOMPONENT);
	health1Object->SetPosition(150, 5);

	//SCORE PLAYER 2
	auto score2Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(score2Object);

	auto score2TextComp = std::shared_ptr<comps::TextComponent>(new comps::TextComponent(font, 64, 28, { 0,255,0 }));
	score2TextComp->SetText("Score: ");

	score2Object->AddComponent(score2TextComp, ComponentType::TEXTCOMPONENT);
	score2Object->SetPosition(300, 5);

	//health PLAYER 2
	auto health2Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(health2Object);

	auto health2TextComp = std::shared_ptr<comps::TextComponent>(new comps::TextComponent(font, 64, 28, { 0,255,0 }));
	health2TextComp->SetText("health: ");

	health2Object->AddComponent(health2TextComp, ComponentType::TEXTCOMPONENT);
	health2Object->SetPosition(430, 5);
}
