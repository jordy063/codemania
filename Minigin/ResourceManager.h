#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		void LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
		std::shared_ptr<dae::Texture2D> GetTexture(const std::string& file);
	private:
		std::map<std::string, std::shared_ptr<Texture2D>> m_pTextures;
	};

}
