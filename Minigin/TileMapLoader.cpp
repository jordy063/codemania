#include "MiniginPCH.h"
#include "TileMapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureComponent.h"


int TileMapLoader::amountOfTextureLayers = 2;

TileMapLoader::TileMapLoader(int amountOfChunks, intPair transformPos, dae::Scene* scene)
	:m_TransformPos{transformPos}
{
    fileStrings[0] = "../Graphics/yellowStripesTile.png";
    fileStrings[1] = "../Graphics/blueStipleTile.png";
    fileStrings[2] = "../Graphics/blueStripeTile.png";
    fileStrings[3] = "../Graphics/GoldTile.png";
 LoadFile(amountOfChunks,scene);

}

void TileMapLoader::LoadFile(int amountOfChunks, dae::Scene* scene) //pass load content
{
    UNREFERENCED_PARAMETER(amountOfChunks);
    std::ifstream myfile;
    myfile.open("../Graphics/levelBubbleBobble.tmx");
    if (myfile.fail())
    {
        std::cout << "could not find file" << std::endl;
    }


    else if (myfile.is_open())
    {
        //read every line seperately
        int index{};
        int chunkIndex{0};
        intPair chunkPos{};
        std::stringstream filetext;
        std::string line;
        int collisionSkipIndex{};
        int xPos{};
        bool collisionDataRead{false};
        
        bool collisionDataLevel1Read{false};
        bool readTextureData{ false };
        bool textureDataRead{false};
        while (std::getline(myfile, line))
        {
            if (textureDataRead == false)
            {
                if (index < 7)
                {
                    ++index;
                }
                else
                {
                    if (line.find("\"") != std::string::npos)
                    {
                        chunkPos = ReadChunkData(line);
                        readTextureData = true;

                    }
                    else if (readTextureData)
                    {

                        if (chunkIndex < 16)
                        {
                            //read that specific chunk
                            ReadTextureData(line, chunkPos, chunkIndex, scene);
                            xPos += TileSize;
                        }
                        else
                        {
                            chunkIndex = -1;
                            readTextureData = false;
                            xPos = 0;

                        }
                        ++chunkIndex;
                    }
                    else if (readTextureData == false)
                    {
                        textureDataRead = true;
                    }

                }
            }
            else if (collisionDataRead == false)
            {
                if (collisionSkipIndex < 2)
                {
                    collisionSkipIndex += 1;
                }
                else if (collisionDataLevel1Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv2 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataLevel1Read = true;
                    }

                    ReadCollisionData(line);
                }
            }

        }
        myfile.close();

    }
    //string[] lines = System.IO.File.ReadAllLines(filename);

    //for (int layerIndex = 0; layerIndex < amountOfTextureLayers; ++layerIndex)
    //{
    //    //ReadLayerProperties(lines);
    //    for (int chunkIndex = 0; chunkIndex < amountOfChunks; chunkIndex++)
    //    {

    //      //  ReadChunkProperties(lines, mapTiles);
    //        Index += 1;

    //    }
    //    Index += 2;
    //}
    //ReadCollisionInfo(lines);
    //ReadCollisionData(lines);

}
intPair TileMapLoader::ReadChunkData(const std::string& sentence)
{

    //read startPos x
    int startIndex = sentence.find_first_of("\"", 0);
    int endIndex = sentence.find_first_of("\"", startIndex + 1);
    std::string substring = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
    int xPos = std::stoi(substring);

    //read startpos y
    startIndex = endIndex + 1;
  
    startIndex = sentence.find_first_of("\"", startIndex + 1);
    endIndex = sentence.find_first_of("\"", startIndex + 1);
    substring = sentence.substr(startIndex + 1, endIndex - startIndex - 1);

    int yPos = std::stoi(substring);

    //use the startposition to calculate further positions of textures
    if (startPosSet == false)
    {
        StartPos.x = xPos;
        StartPos.y = yPos;
        startPosSet = true;
    }

    startIndex = endIndex;

    startIndex = sentence.find_first_of("\"", startIndex + 1);
    endIndex = sentence.find_first_of("\"", startIndex + 1);
    substring = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
    ChunkWidth = std::stoi(substring);

    startIndex = endIndex;

    startIndex = sentence.find_first_of("\"", startIndex + 1);
    endIndex = sentence.find_first_of("\"", startIndex + 1);
    substring = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
    ChunkHeight = std::stoi(substring);

    return { xPos,yPos };

}
void TileMapLoader::ReadTextureData(const std::string& sentence,intPair chunkPos,int row, dae::Scene* scene)
{

    int start = 0;
    for (int j = 0; j < ChunkWidth; ++j)
    {

        int indexOfComma = sentence.find_first_of(",", start);
        if (j == 15)
        {
            std::string lastNumber = sentence.substr(start, sentence.length() - start);

            int spriteIndexOfLast = std::stoi(lastNumber);
            if (spriteIndexOfLast != 0)
            {
                intPair testPos{ (chunkPos.x - StartPos.x) * TileSize + j * TileSize, (chunkPos.y - StartPos.y) * TileSize + row * TileSize };
                std::cout << testPos.x << ", " << testPos.y << '\n';
                int newIndex = spriteIndexOfLast - 1;

                auto TileObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
               
                TileObject->GetTransform()->Translate(float(testPos.x),float( testPos.y));
                std::string test = fileStrings[newIndex];
                // for next line seperate the texturefile to 4 cause we can't split it. have a string with all filenames that are according to the data written
                auto TextureComp = std::shared_ptr<comps::TextureComponent>(new comps::TextureComponent(fileStrings[newIndex], TileSize, TileSize));
                TileObject->AddComponent(TextureComp);
                scene->Add(TileObject);
            }
                //PngTiles.Add(new Tile(mapTiles[spriteIndexOfLast - 1], new Vector2((xPos - StartPos.X) * ChunkWidth + j * 16 + (int)TransformPos.X, (yPos - StartPos.Y) * ChunkHeight + i * 16 + (int)TransformPos.Y)));
        }
        else if (indexOfComma != -1)
        {

            std::string last = sentence.substr(start, indexOfComma - start);

            if (last != "")
            {
                int spriteIndex = std::stoi(last);
                if (spriteIndex != 0)
                {
                    intPair testPos{ (chunkPos.x - StartPos.x) * TileSize + j * TileSize, (chunkPos.y - StartPos.y) * TileSize + row * TileSize };
                    std::cout << testPos.x << ", " << testPos.y << '\n';
                    int newIndex = spriteIndex - 1;

                    auto TileObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
                    TileObject->GetTransform()->Translate(float(testPos.x),float( testPos.y));
                    std::string test = fileStrings[newIndex];
                    // for next line seperate the texturefile to 4 cause we can't split it. have a string with all filenames that are according to the data written
                    auto TextureComp = std::shared_ptr<comps::TextureComponent>(new comps::TextureComponent(fileStrings[newIndex], TileSize, TileSize));
                    
                    TileObject->AddComponent(TextureComp);
                    
                    scene->Add(TileObject);
                    //PngTiles.Add(new Tile(mapTiles[spriteIndex - 1], new Vector2((xPos - StartPos.X) * ChunkWidth + j * 16 + (int)TransformPos.X, (yPos - StartPos.Y) * ChunkHeight + i * 16 + (int)TransformPos.Y)));
                }
            }
           
        }
        start = indexOfComma + 1;

    }
}
void TileMapLoader::ReadCollisionData(const std::string& sentence)
{
    //read all the collision
    int startIndex = sentence.find_first_of("\"", 0);

        //read ID
        int endIndex = sentence.find_first_of("\"", startIndex + 1);
        

        //read x
        startIndex = endIndex + 1;

        startIndex = sentence.find_first_of("\"", startIndex);
        endIndex = sentence.find_first_of("\"", startIndex + 1);
        std::string test = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
        int XPos = std::stoi(test);

        //read y
        startIndex = endIndex + 1;

        startIndex = sentence.find_first_of("\"", startIndex);
        endIndex = sentence.find_first_of("\"", startIndex + 1);
        test = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
        int YPos = std::stoi(test);

        //read with
        startIndex = endIndex + 1;

        startIndex = sentence.find_first_of("\"", startIndex);
        endIndex = sentence.find_first_of("\"", startIndex + 1);
        test = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
        int width = std::stoi(test);

        //read height
        startIndex = endIndex + 1;

        startIndex = sentence.find_first_of("\"", startIndex);
        endIndex = sentence.find_first_of("\"", startIndex + 1);
        test = sentence.substr(startIndex + 1, endIndex - startIndex - 1);
        int height = std::stoi(test);

        //with info, add collision rectangle to list
        auto rect = std::shared_ptr<rectangle_>(new rectangle_ { XPos, YPos, width, height });

        //works as intended but 
        m_CollisionTiles.push_back(rect);
    

}

