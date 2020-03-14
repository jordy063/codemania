#pragma once
#include "CollisionRectangle.h"
#include <list>
#include "GameObject.h"
class TileMapLoader
{
public:
    TileMapLoader(std::wstring filename, int amountOfChunks, float2 transformPos);
    std::list<std::shared_ptr<dae::GameObject>> GetCollisionTiles() const { ; return m_CollisionTiles; };
private:
    std::list<std::shared_ptr<dae::GameObject>> PngTiles;
    std::list<std::shared_ptr<dae::GameObject>> m_CollisionTiles;
    int ChunkWidth;
    int ChunkHeight;
    int Index = 5;
    float2 StartPos;
    static int amountOfTextureLayers;
    float2 TransformPos;
};

