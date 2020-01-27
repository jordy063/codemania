#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include "Renderer.h"


comps::SpriteComponent::SpriteComponent(std::string filename,int rows, int colls, int frameBegin, int frameEnd, float UpdateSpeed)
	:m_Rows{rows}
	,m_Colls{colls}
	,m_FrameBegin{frameBegin}
	,m_FrameEnd{frameEnd}
	,m_UpdateSpeed{UpdateSpeed}
	,m_FrameNumber{frameBegin}
	,TextureComponent{ filename }
{
}

comps::SpriteComponent::~SpriteComponent()
{
}

void comps::SpriteComponent::Initialize(const dae::Scene & scene)
{
	UNREFERENCED_PARAMETER(scene);
	
}

void comps::SpriteComponent::Update(const dae::Scene & scene,float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

	m_Timer += elapsedSecs;

	//timer/update updates from 0 - ..., floor rounds it to the lowest int, % makes it so that you get 0 % 4 for example which is 0(it updates 0,1,2,3,0
	m_FrameNumber = m_FrameBegin + int(floor(m_Timer / m_UpdateSpeed)) % (m_FrameEnd - m_FrameBegin);



	TextureComponent::Update(scene, elapsedSecs, pos);

}

void comps::SpriteComponent::Render(const dae::Scene & scene, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	
	int width = m_pTexture->GetSize().first / m_Colls;
	int height = m_pTexture->GetSize().second / m_Rows;

	int x = m_FrameNumber % m_Colls;
	int y = m_FrameNumber / m_Colls;

	Rectangle_ srcRect{ x*width,y*height,width,height };

	if (m_pTexture != nullptr)
	{
		
		auto texSize = m_pTexture->GetSize();
		int xShift = int(m_Offset.x) + (texSize.first * (int)m_Alignment.first) / 2;
		int yShift = int(m_Offset.y) + (texSize.second * (int)m_Alignment.second) / 2;
		dae::Renderer::GetInstance().RenderTextureCutOut(*m_pTexture, pos.x - xShift, pos.y - yShift, srcRect);
	}
}
