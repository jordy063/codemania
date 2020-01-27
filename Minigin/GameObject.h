#pragma once
#include <memory>

#include "Transform.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "Scene.h"



namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		
		void Render() const override;
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

		void AddComponent(std::shared_ptr<comps::BaseComponent> comp);
		void ChangeScene(Scene* newScene);


		void Initialize();
		void PostInitialize(const Scene&) {};
		void PostDraw(const Scene&) {};

		

	private:
		
		std::shared_ptr <TransformComponent> m_pTransform;
		std::vector<std::shared_ptr<comps::BaseComponent>> m_pComponents;
		Scene* m_pScene;


		
	};
}