#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
namespace dae
{
	class GameObject;
}
namespace comps
{
	class BoundingBoxComponent;
}
namespace comps
{
	class ItemComponent final : public comps::BaseComponent
	{
	public:
		ItemComponent(std::shared_ptr<dae::GameObject> pPlayerObject);
		~ItemComponent() = default;;

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	private:
		std::shared_ptr<comps::BoundingBoxComponent> m_pPlayerBoundingBox;
		
		int m_StartHealth;
	};
}