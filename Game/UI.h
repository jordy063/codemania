#pragma once
namespace comps
{
	class TextureComponent;
}
namespace dae
{
	class Font;
}

class UI
{
public:
	UI();
	void Initialize();
private:
	std::string m_FileName;
	std::shared_ptr<dae::Font> m_pFont;
};

