#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "LevelManager.h"



comps::SpriteComponent::SpriteComponent(std::string filename,int rows, int colls, int spriteIndex,float updateSpeed,float width,float height)
	:m_Rows{rows}
	,m_Colls{colls}
	,m_FrameBegin{ spriteIndex*2 * colls}
	,m_FrameEnd{ spriteIndex * 2 + 1* colls }
	,m_UpdateSpeed{ updateSpeed }
	,m_FrameNumber{ spriteIndex * 2 }
	, TextureComponent{ filename,width,height }
	, m_Timer{}
	, m_SpriteIndex{spriteIndex}

{
}

comps::SpriteComponent::~SpriteComponent()
{
	
}

void comps::SpriteComponent::SetActiveRow(int row)
{
	//calculate which row is asked with the spriteID
	//row + id*2
	int actualRow = row + m_SpriteIndex * 2;
	SetBeginEndFrames(actualRow *m_Colls, actualRow *m_Colls + m_Colls);
}

void comps::SpriteComponent::SetActiveRowStop()
{
	SetBeginEndFrames(m_FrameBegin, m_FrameBegin+1);
}

void comps::SpriteComponent::SetBeginEndFrames(int beginFrame, int endFrame)
{
	m_FrameBegin = beginFrame;
	m_FrameEnd = endFrame;
}

void comps::SpriteComponent::SetBeginEndFrames(int beginFrame, int endFrame,int collsApart)
{
	m_FrameBegin = beginFrame + m_SpriteIndex* collsApart;
	m_FrameEnd = endFrame + m_SpriteIndex * collsApart;
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
	if (m_FrameBegin != m_FrameEnd)
		m_FrameNumber = m_FrameBegin + int(floor(m_Timer / m_UpdateSpeed)) % (m_FrameEnd - m_FrameBegin);
	else
		m_FrameNumber = m_FrameBegin;
	



	TextureComponent::Update(scene, elapsedSecs, pos);

}

void comps::SpriteComponent::Render(const dae::Scene & scene, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	
	float width = float(m_pTexture->GetSize().first / m_Colls);
	float height = float(m_pTexture->GetSize().second / m_Rows);

	int x = m_FrameNumber % m_Colls;
	int y = m_FrameNumber / m_Colls;

	rectangle_ srcRect{ x*width,y*height,width,height };

	if (m_pTexture != nullptr)
	{
		
		auto texSize = m_pTexture->GetSize();
		int xShift = int(m_Offset.x) + (texSize.first * (int)m_Alignment.first) / 2 + (int)LevelManager::GetInstance().GetTranslationX();
		int yShift = int(m_Offset.y) + (texSize.second * (int)m_Alignment.second) / 2 + (int)LevelManager::GetInstance().GetTranslationY();
		dae::Renderer::GetInstance().RenderTextureCutOut(*m_pTexture, pos.x - xShift, pos.y - yShift, srcRect,m_Width,m_Height);
	}
}
