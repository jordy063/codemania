#pragma once
#include <vector>
#include "HealthComponent.h"
namespace comps
{
	class TextureComponent;
	class HealthComponent;
	class ShowScoreComponent;
}
namespace dae
{
	class GameObject;
	class Font;
}

class UI
{
public:
	UI(std::shared_ptr<dae::GameObject> pPlayer);
	void Initialize();
	void AddPlayer2(std::shared_ptr<dae::GameObject> pPlayer2);
	void Reset();
private:
	std::string m_FileName;
	std::shared_ptr<dae::Font> m_pFont;
	std::vector<std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;
	std::shared_ptr<comps::ShowScoreComponent> m_pScoreComp;
	std::shared_ptr <dae::GameObject> m_pPlayer2HealthObject;
};

