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

UI::UI(std::shared_ptr<dae::GameObject> pPlayer)
	:m_FileName{ "../Graphics/UIBar.png" }
{

	auto healthComp = pPlayer->GetComponent(ComponentType::HEALTHCOMPONENT);
	m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));
	
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

	m_pScoreComp = std::shared_ptr<comps::ShowScoreComponent>(new comps::ShowScoreComponent(m_pFont, 64, 28, { 0,255,0 }));
	m_pScoreComp->SetText("Score: 0");

	score1Object->AddComponent(m_pScoreComp, ComponentType::SHOWSCORECOMPONENT);
	score1Object->SetPosition(270, 5);

	

	//health PLAYER 1
	auto health1Object = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(health1Object);

	auto health1TextComp = std::shared_ptr<comps::ShowHealthComponent>(new comps::ShowHealthComponent(m_pFont, 64, 28, { 0,255,0 },m_pPlayerHealthComps[0]));
	health1TextComp->SetText("health: 4");

	health1Object->AddComponent(health1TextComp, ComponentType::SHOWHEALTHCOMPONENT);
	health1Object->SetPosition(150, 5);

	

	
	
	
}

void UI::AddPlayer2(std::shared_ptr<dae::GameObject> pPlayer2)
{
	auto healthComp = pPlayer2->GetComponent(ComponentType::HEALTHCOMPONENT);
	m_pPlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(healthComp));

	//health PLAYER 2
	m_pPlayer2HealthObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());

	dae::SceneManager::GetInstance().GetActiveScene()->Add(m_pPlayer2HealthObject);

	auto health2TextComp = std::shared_ptr<comps::ShowHealthComponent>(new comps::ShowHealthComponent(m_pFont, 64, 28, { 0,255,0 }, m_pPlayerHealthComps[1]));
	health2TextComp->SetText("health: 4");

	m_pPlayer2HealthObject->AddComponent(health2TextComp, ComponentType::SHOWHEALTHCOMPONENT);
	m_pPlayer2HealthObject->SetPosition(400, 5);
}

void UI::Reset()
{
	//we only reset the first one because the other player gets remade

	if (m_pPlayer2HealthObject != nullptr)
	{
		m_pPlayer2HealthObject->Clear();
		m_pPlayerHealthComps.pop_back();
	}
	m_pPlayerHealthComps[0]->ResetHealth();
	
	m_pScoreComp->SetText("Score: 0");
}
