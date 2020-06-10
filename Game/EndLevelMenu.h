#pragma once
#include "Singleton.h"
#include <map>
#include "Texture2D.h"
#include "Font.h"
#include "EndMenuObserver.h"

enum class EndLevelMenuItem
{
	PLAYAGAIN,
	QUIT,
};

class EndLevelMenu final : public dae::Singleton< EndLevelMenu>
{
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

private:
	bool m_IsQuitCalled = false;
	const std::string m_Language{ "nl" };
	std::map<EndLevelMenuItem, std::string> m_MenuMap;
	std::map<EndLevelMenuItem, std::shared_ptr<dae::Texture2D>> m_pMenuTextures;
	std::map<EndLevelMenuItem, std::shared_ptr<dae::Texture2D>> m_pSelectedMenuTextures;
	std::shared_ptr<dae::Texture2D> m_pTitleTexture;
	std::shared_ptr<dae::Font> m_pFont;
	int m_ButtonAmount = 2;
	int m_SelectIndex;
	int m_DeathId = -1;
	std::shared_ptr<EndMenuObserver> m_pEndMenuObserver;

	bool readLanguageParameters(const std::string& line, const std::string& language);
	void FillInTexture(std::map<EndLevelMenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures, SDL_Color color);
	void FillInTitle(SDL_Color color);
	void RenderMenuItems();
};

