#pragma once
#include "TextureComponent.h"

namespace comps
{
	class SpriteComponent : public TextureComponent
	{
	public:
		SpriteComponent(std::string filename, int rows,int colls,int frameBegin,int frameEnd,float UpdateSpeed);
		~SpriteComponent();
		void SetActiveRow(int row);
		void SetBeginEndFrames(int beginFrame, int endFrame);
		void SetActiveRowStop();

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene,float elapsedSecs, float2 pos) override;
		virtual void Render(const dae::Scene& scene, float2 pos) override;

	private:
		int m_FrameNumber;
		const float m_UpdateSpeed;
		const int m_Rows;
		const int m_Colls;
		int m_FrameBegin;
		int m_FrameEnd;
		float m_Timer;


	};
}

