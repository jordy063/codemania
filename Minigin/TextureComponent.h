#pragma once
#include "BaseComponent.h"


namespace dae
{
	class Texture2D;
}
namespace comps
{

	class TextureComponent : public comps::BaseComponent
	{

	public:
		TextureComponent(const std::string& filename,float width,float height, bool allowScrolling = true);
		TextureComponent(float width, float height);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		void SetTexture(const std::string& filename);
		void SetOffset(float2 offset);
		void SetAlignment(HAlign hAlign, VAlign vAlign);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
		virtual void Render(const dae::Scene& scene, float2 pos) override;

		bool m_NeedsUpdate;
		std::shared_ptr<dae::Texture2D> m_pTexture;
		std::pair< HAlign, VAlign> m_Alignment;
		float2 m_Offset;
		float m_Width;
		float m_Height;
		bool m_AllowScrolling;

	private:
		
		
	};
}
