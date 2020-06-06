#pragma once
#include <memory>

#include "Transform.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "Scene.h"
#include <map>

class TileMapLoader;

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		
		void Render() override;
		void Update(float elapsedSecs) override;
		void SetPosition(float x, float y);
		void SetScale(float x, float y);

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		std::shared_ptr <TransformComponent> GetTransform() const { return m_pTransform; }

		void AddComponent(std::shared_ptr<comps::BaseComponent> comp, ComponentType type);
		void ChangeScene(Scene* newScene);
		void Clear();
		void Disable();
		void Enable();


		void Initialize();
		void PostInitialize(const Scene&) {};
		void PostDraw(const Scene&) {};
		void RegisterTileMap(std::shared_ptr<TileMapLoader> tileMapLoader);
		std::shared_ptr<TileMapLoader> GetTileMap() { return m_pTileMap; }

		//template <class T>
		//bool HasComponent()
		//{
		//	return GetComponent<T>() != nullptr;
		//}

		//template <class T>
		std::shared_ptr<comps::BaseComponent> GetComponent(ComponentType type)
		{
			unsigned int key = type;
			if(key >= 0 && key <= ComponentType::FPSCOMPONENT)
			return m_pComponents[key];
			
			
			return nullptr;
		}

	private:
		std::shared_ptr <TransformComponent> m_pTransform;
		std::map<int,std::shared_ptr<comps::BaseComponent>> m_pComponents;
		//std::vector<std::shared_ptr<comps::BaseComponent>> m_pComponents;
		Scene* m_pScene;
		std::shared_ptr<TileMapLoader> m_pTileMap;
		std::vector<ComponentType> m_Types;
		bool m_IsEnabled;
		
	};
}
