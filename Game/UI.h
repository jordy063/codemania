#pragma once
#include <vector>
#include "HealthComponent.h"
namespace comps
{
	class TextureComponent;
}
namespace dae
{
	class GameObject;
	class Font;
}

class UI
{
public:
	UI(std::vector<std::shared_ptr<dae::GameObject>> pPlayers);
	void Initialize();
	void AddPlayer2();
private:
	std::string m_FileName;
	std::shared_ptr<dae::Font> m_pFont;
	std::vector<std::shared_ptr<comps::HealthComponent>> m_pPlayerHealthComps;
};

