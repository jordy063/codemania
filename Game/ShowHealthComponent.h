#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
namespace comps
{
	class HealthComponent;
}
namespace comps
{

	class ShowHealthComponent final : public comps::TextComponent
	{
	public:
		ShowHealthComponent(std::shared_ptr<dae::Font> font, float width, float height, SDL_Color color,std::shared_ptr< comps::HealthComponent> pHealthComp);
		using TextComponent::TextComponent;

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	private:
		int m_Health = 4;
		std::shared_ptr< comps::HealthComponent> m_pHealthComp;
	};


}