#pragma once
#include "SceneObject.h"
#include "TransformComponent.h"

namespace dae
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
	class Font;
	class Texture2D;

	class TextObject : public SceneObject
	{
	public:
		void Update(float elapsedSecs) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetAlignment(HAlign hAlign, VAlign vAlign);

		explicit TextObject(const std::string& text, std::shared_ptr<Font> font);
		~TextObject();
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:


		bool mNeedsUpdate;
		std::string mText;
		TransformComponent* m_pTransform;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;
		std::pair< HAlign, VAlign> m_Alignment;
	
	};

}
