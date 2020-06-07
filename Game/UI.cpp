#include "MiniginPCH.h"
#include "UI.h"
#include "GameObject.h"
#include <shared_mutex>
#include "TextureComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "ShowScoreComponent.h"
#include "ShowHealthComponent.h"
#include "Font.h"
#include "Menu.h"

UI::UI(std::vector<std::shared_ptr<dae::GameObject>> pPlayers)
	:m_FileName{ "../Graphics/UIBar.png" }
{
	for (std::shared_ptr<dae::GameObject> pPlayer : pPlayers)
	{
		auto healthComp = pPlayer->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));
	}
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
	m_pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	dae::SceneManager::GetInstance().GetActiveScene()->Add(score1Object);

	auto score1TextComp = std::shared_ptr<comps::ShowScoreComponent>(new comps::ShowScoreComponent(m_pFont, 64, 28, { 0,255,0 }));
	score1TextComp->SetText("Score: 0");

	score1Object->AddComponent(score1TextComp, ComponentType::SHOWSCORECOMPONENT);
	score1Object->SetPosition(270, 5);

	

	//health PLAYER 1
	auto health1Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(health1Object);

	auto health1TextComp = std::shared_ptr<comps::ShowHealthComponent>(new comps::ShowHealthComponent(m_pFont, 64, 28, { 0,255,0 },m_pPlayerHealthComps[0]));
	health1TextComp->SetText("health: 3");

	health1Object->AddComponent(health1TextComp, ComponentType::SHOWHEALTHCOMPONENT);
	health1Object->SetPosition(150, 5);

	

	
	
	
}

void UI::AddPlayer2()
{
	//health PLAYER 2
	auto health2Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(health2Object);

	auto health2TextComp = std::shared_ptr<comps::ShowHealthComponent>(new comps::ShowHealthComponent(m_pFont, 64, 28, { 0,255,0 }, m_pPlayerHealthComps[1]));
	health2TextComp->SetText("health: 3");

	health2Object->AddComponent(health2TextComp, ComponentType::SHOWHEALTHCOMPONENT);
	health2Object->SetPosition(400, 5);
}
