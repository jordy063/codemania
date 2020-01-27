#pragma once
#include "structs.h"

namespace dae
{
	class GameObject;
	class Scene;
}



namespace comps
{
	enum HAlign {
		LEFT = 0,
		CENTER = 1,
		RIGHT = 2
	};
	enum VAlign
	{
		TOP = 0,
		MIDDLE = 1,
		BOTTOM = 2
	};

	class BaseComponent
	{
		friend class dae::GameObject;
		void RootInitialize(const dae::Scene& scene);
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		~BaseComponent();

		//dae::GameObject* GetGameObject() const { return m_pGameObject; }
		//Transform GetTransform() const;

	protected:
		virtual void Initialize(const dae::Scene& scene) = 0;
		virtual void Update(const dae::Scene& scene,float elapsedSecs, float2 pos) = 0;
		virtual void Render(const dae::Scene& scene, float2 pos) = 0;

		
		bool m_IsInitialized;
	};

}