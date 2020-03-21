#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
namespace comps
{
	
	class FpsComponent final: public comps::TextComponent
	{
	public:
		using TextComponent::TextComponent;

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	

	};


}

