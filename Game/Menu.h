#pragma once
#include "structs.h"
#include <string>
#include <map>
#include "Singleton.h"
#include "Texture2D.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MenuObserver.h"

namespace comps
{
	class TextureComponent;
}

enum MenuItem
{
	P1PLAY,
	P2PLAY,
	QUIT
};

class Menu final: public dae::Singleton<Menu>
{
	friend class comps::TextureComponent;
public:
	void readDataFromJSON();

	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	bool GetShowMenu() const { return m_ShowMenu; }
	void SetShowMenu(bool showMenu);
	void MoveUp();
	void MoveDown();
	void Confirm();
	bool GetIsQuitCalled() const { return m_IsQuitCalled; }
	void RegisterPlayer2(std::shared_ptr<dae::GameObject> pPlayer);
	
private:
	std::shared_ptr<dae::GameObject> m_pPlayer;
	std::string m_Filename;
	std::map<MenuItem, std::string> m_MenuMap;
	std::map<MenuItem, std::shared_ptr<dae::Texture2D>> m_pMenuTextures;
	std::map<MenuItem, std::shared_ptr<dae::Texture2D>> m_pSelectedMenuTextures;
	int m_SelectIndex;
	std::shared_ptr<dae::Font> m_pFont;
	bool m_ShowMenu = true;
	std::shared_ptr<MenuObserver> m_pMenuObserver;

	bool readLanguageParameters(const std::string& line, const std::string& languagee);
	void makeGameObject();
	bool m_IsQuitCalled = false;
	void FillInTexture(std::map<MenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures, SDL_Color color);
	void RenderMenuItems();
	void RenderTexture(std::shared_ptr<dae::Texture2D> pTexture, float2 offset, float2 pos, float2 dimensions);

	//textures
	std::shared_ptr<dae::Texture2D> m_pTitleTexture;
};

