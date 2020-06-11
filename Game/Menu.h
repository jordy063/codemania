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
	P2VERSUS,
	QUIT,
	CONTROLLERSOFF,
	CONTROLLERSON
};
//we should have a vector with 2 textures

class Menu final: public dae::Singleton<Menu>
{
	friend class comps::TextureComponent;
public:
	void readDataFromJSON();

	virtual void Initialize();
	virtual void Update(float elapsedSecs);
	virtual void Render();
	void SetShowMenu(bool showMenu);
	void MoveUp();
	void MoveDown();
	void Confirm();
	bool GetIsQuitCalled() const { return m_IsQuitCalled; }
	void RegisterPlayer2(std::shared_ptr<dae::GameObject> pPlayer);
	void CheckChangeControllers();
	bool GetUseControllers() const { return m_UseControllers; }
	void ResetMenu();
	
private:
	bool m_MaySelect = false;
	float m_SelectTimer{};
	const float m_SelectTime{ 2 };
	std::shared_ptr<dae::GameObject> m_pPlayer;
	std::string m_Filename;
	//std::vector< std::shared_ptr<dae::Texture2D>> m_pOnOffTextures;
	std::map<MenuItem, std::string> m_MenuMap;
	std::map<MenuItem, std::shared_ptr<dae::Texture2D>> m_pMenuTextures;
	std::map<MenuItem, std::shared_ptr<dae::Texture2D>> m_pSelectedMenuTextures;
	int m_SelectIndex;
	std::shared_ptr<dae::Font> m_pFont;
	bool m_ShowMenu = true;
	int m_ButtonAmount = 5;
	std::shared_ptr<MenuObserver> m_pMenuObserver;
	bool m_UseControllers = false;
	const std::string m_Language{ "nl" };
	//textures
	std::shared_ptr<dae::Texture2D> m_pTitleTexture;
	bool m_IsQuitCalled = false;

	bool readLanguageParameters(const std::string& line, const std::string& languagee);
	void FillInTexture(std::map<MenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures, SDL_Color color);
	void RenderMenuItems();
	void RenderTexture(std::shared_ptr<dae::Texture2D> pTexture, float2 offset, float2 pos, float2 dimensions);

};

