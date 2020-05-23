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
	
	
private:
	float2 m_Position;
	std::string m_Filename;
	std::map<std::string, std::string> m_MenuMap;
	std::map<std::string, std::shared_ptr<dae::Texture2D>> m_pMenuTextures;
	int m_SelectIndex;
	std::shared_ptr<dae::Font> m_pFont;
	bool m_ShowMenu = true;
	std::shared_ptr<MenuObserver> m_pMenuObserver;

	bool readLanguageParameters(const std::string& line, const std::string& languagee);
	void makeGameObject();


	
};

