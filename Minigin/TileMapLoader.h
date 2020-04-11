#pragma once
#include <list>
#include "GameObject.h"
#include "Singleton.h"
class TileMapLoader final : public dae::Singleton< TileMapLoader>
{
public:
    TileMapLoader( int amountOfChunks, intPair transformPos,std::shared_ptr<dae::Scene> scene);
    std::list<std::shared_ptr<rectangle_>> GetCollisionTiles() const { ; return m_CollisionTiles; };
private:
    std::list<std::shared_ptr<dae::GameObject>> PngTiles;
    std::list<std::shared_ptr<rectangle_>> m_CollisionTiles;
    int ChunkWidth;
    int ChunkHeight;
    int Index = 5;
    intPair StartPos;
    bool startPosSet;
    static int amountOfTextureLayers;   
    intPair m_TransformPos;
    void LoadFile(int amountOfChunks, std::shared_ptr<dae::Scene> scene);
    intPair ReadChunkData(const std::string& sentence);
    void ReadTextureData(const std::string& sentence, intPair chunkPos, int row, std::shared_ptr<dae::Scene> scene);
    void ReadCollisionData(const std::string& sentence);
    std::string fileStrings[4];
    const static int TileSize{24};

    //png tiles are components which are added to the game object.
    //png's might have to be seperate
};

