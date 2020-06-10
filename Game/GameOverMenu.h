#pragma once
#include "Singleton.h"
#include <map>
#include "Texture2D.h"
#include "Font.h"
#include "GameOverMenuObserver.h"

namespace comps
{
	class TextureComponent;
}

enum class GameOverMenuItem
{
	PLAYAGAIN,
	QUIT,
};

class GameOverMenu final : public dae::Singleton<GameOverMenu>
{
	friend class comps::TextureComponent;
public:
	void readDataFromJSON();

	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	void SetShowMenu(bool showMenu);
	void MoveUp();
	void MoveDown();
	void Confirm();
	bool GetIsQuitCalled() const { return m_IsQuitCalled; }
	void RegisterDeath(int id);

private:
	bool m_IsQuitCalled = false;
	const std::string m_Language{ "nl" };
	std::map<GameOverMenuItem, std::string> m_MenuMap;
	std::map<GameOverMenuItem, std::shared_ptr<dae::Texture2D>> m_pMenuTextures;
	std::map<GameOverMenuItem, std::shared_ptr<dae::Texture2D>> m_pSelectedMenuTextures;
	std::vector< std::shared_ptr<dae::Texture2D>> m_pTitleTextures;
	std::shared_ptr<dae::Font> m_pFont;
	int m_ButtonAmount = 2;
	int m_SelectIndex;
	int m_DeathId = -1;
	std::shared_ptr<GameOverMenuObserver> m_pGameOverMenuObserver;

	bool readLanguageParameters(const std::string& line, const std::string& language);
	void FillInTexture(std::map<GameOverMenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures, SDL_Color color);
	void FillInTitle( SDL_Color color);
	void RenderMenuItems();

};