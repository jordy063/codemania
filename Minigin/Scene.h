#pragma once
#include "SceneManager.h"
#include "Entity.h"
#include "FPSCounter.h"
namespace comps 
{
	class TextComponent;
}
namespace dae
{
	class SceneObject;
	class GameObject;
	
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);
		void Add(const std::shared_ptr<Entity>& object);
		void AddGameObject(const std::shared_ptr<GameObject>& object);

		void Initialize();
		void Update(float elapsedSecs);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		

	protected:
		bool CreateFPSCounter();

	private: 
		explicit Scene(const std::string name);

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};
		std::shared_ptr<FPSCounter> m_pFPSCounter;
		

		float m_Lag;
		int m_Frames;

		static unsigned int idCounter; 
	};

}
