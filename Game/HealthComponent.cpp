#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameOverMenu.h"
#include "GameInfo.h"
#include "LevelManager.h"
#include "SoundManager2.h"

comps::HealthComponent::HealthComponent(int health,int id)
	:m_Health(health)
	, m_StartHealth(health)
	, m_InvinsibleTime(2)
	, m_InvinsibleTimer(0)
	, m_Id(id)
	, m_TransitionTimer()
	, m_TransitionTime(8)
{
}

void comps::HealthComponent::DropHealth(int amount)
{
	//if we transition we're invincible
	if (m_IsTransisioning == false)
	{
		//we take some damage but then have a small timer to get out of danger
		if (m_Health > 0 && m_IsInvisble == false)
		{
			m_Health -= amount;
			m_IsInvisble = true;
			LevelManager::GetInstance().ResetPlayerPos(m_Id);
			std::string filename{ "../Sounds/loseHealthSound.wav" };
			SoundManager2::GetInstance().playEffect(filename);
		}
		//health = 0 so gameover
		if (m_Health <= 0)
		{
			std::string filename{ "../Sounds/deathSound.wav" };
			SoundManager2::GetInstance().playEffect(filename);
			GameOverMenu::GetInstance().RegisterDeath(m_Id);
			GameInfo::GetInstance().SetGameState(GameState::GAMEOVERMENU);
		}
	}
	

}

void comps::HealthComponent::ResetHealth()
{
	m_Health = m_StartHealth;
}

void comps::HealthComponent::SetIsTransitioning()
{
	//gets called in enemyObserver when level gets updated
	m_IsTransisioning = true;
	m_TransitionTimer = 0;
}

void comps::HealthComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::HealthComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	//we check if the timers expire 
	if (m_IsInvisble)
	{
		m_InvinsibleTimer += elapsedSecs;
		if (m_InvinsibleTimer > m_InvinsibleTime)
		{
			m_InvinsibleTimer = 0;
			m_IsInvisble = false;
		}

	}
	if (m_IsTransisioning)
	{
		m_TransitionTimer += elapsedSecs;
		if (m_TransitionTimer > m_TransitionTime)
		{
			m_IsTransisioning = false;
		}
	}
}
