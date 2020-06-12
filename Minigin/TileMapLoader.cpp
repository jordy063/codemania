#include "MiniginPCH.h"
#include "TileMapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureComponent.h"


int TileMapLoader::amountOfTextureLayers = 2;

TileMapLoader::TileMapLoader(int amountOfChunks, float2 transformPos, std::shared_ptr<dae::Scene> scene)
    :m_TransformPos{ transformPos }
{
    fileStrings[0] = "../Graphics/yellowStripesTile.png";
    fileStrings[1] = "../Graphics/blueStipleTile.png";
    fileStrings[2] = "../Graphics/blueStripeTile.png";
    fileStrings[3] = "../Graphics/GoldTile.png";
    m_CurrentLevel = 0;
    LoadFile(amountOfChunks, scene);


}

std::list<std::shared_ptr<rectangle_>> TileMapLoader::GetCollisionWalls() const
{
    switch (m_CurrentLevel)
    {
    case 0:
        return m_CollisionWalls1;
        break;
    case 1:
        return m_CollisionWalls2;
        break;
    case 2:
        return m_CollisionWalls3;
        break;
    default:
        std::cout << "level does not exist" << std::endl;
        break;
    }
    return std::list<std::shared_ptr<rectangle_>>();

}

void TileMapLoader::UpdateLevel(int level)
{
    m_CurrentLevel = level;
}

std::list<std::shared_ptr<rectangle_>> TileMapLoader::GetCollisionPlatforms() const
{
    switch (m_CurrentLevel)
    {
    case 0:
        return m_CollisionPlatforms1;
        break;
    case 1:
        return m_CollisionPlatforms2;
        break;
    case 2:
        return m_CollisionPlatforms3;
        break;
    default:
        std::cout << "level does not exist" << std::endl;
        break;
    }

    return std::list<std::shared_ptr<rectangle_>>();
}

void TileMapLoader::LoadFile(int amountOfChunks, std::shared_ptr<dae::Scene> scene) //pass load content
{
    UNREFERENCED_PARAMETER(amountOfChunks);
    std::ifstream myfile;
    myfile.open("../Graphics/BubbleBobbleLevel.tmx");
    if (myfile.fail())
    {
        std::cout << "could not find file" << std::endl;
    }


    else if (myfile.is_open())
    {
        //read every line seperately
        int index{};
        int chunkIndex{ 0 };
        intPair chunkPos{};
        std::stringstream filetext;
        std::string line;
        int collisionSkipIndex{};
        int xPos{};
        bool collisionDataRead{ false };

        bool collisionDataWalls1Read{ false };
        bool collisionDataPlatforms1Read{ false };
        bool collisionDataWalls2Read{ false };
        bool collisionDataPlatforms2Read{ false };
        bool collisionDataWalls3Read{ false };
        bool collisionDataPlatforms3Read{ false };
        bool readTextureData{ false };
        bool textureDataRead{ false };
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
                else if (collisionDataWalls1Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv1 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataWalls1Read = true;
                        collisionSkipIndex = 1;
                    }
                    else
                        ReadCollisionData(line, m_CollisionWalls1);
                }
                else if (collisionDataPlatforms1Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv1 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataPlatforms1Read = true;
                        collisionSkipIndex = 1;

                    }
                    else
                        ReadCollisionData(line, m_CollisionPlatforms1);

                }
                else if (collisionDataWalls2Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv2 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataWalls2Read = true;
                        collisionSkipIndex = 1;

                    }
                    else
                        ReadCollisionData(line, m_CollisionWalls2);

                }
                else if (collisionDataPlatforms2Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv2 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataPlatforms2Read = true;
                        collisionSkipIndex = 1;

                    }
                    else
                        ReadCollisionData(line, m_CollisionPlatforms2);

                }
                else if (collisionDataWalls3Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv3 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataWalls3Read = true;
                        collisionSkipIndex = 1;

                    }
                    else
                        ReadCollisionData(line, m_CollisionWalls3);

                }
                else if (collisionDataPlatforms3Read == false)
                {
                    //check the values

                    //at the end, if the value isn't valid we set the bool to true and collisiondata lv3 = true
                    if (line.find("\"") == std::string::npos)
                    {
                        collisionDataPlatforms3Read = true;
                        collisionSkipIndex = 1;
                        myfile.close();
                    }
                    else
                        ReadCollisionData(line, m_CollisionPlatforms3);

                }
            }


        }


    }


}
intPair TileMapLoader::ReadChunkData(const std::string& sentence)
{

    //read startPos x
    size_t startIndex = sentence.find_first_of("\"", 0);
    size_t endIndex = sentence.find_first_of("\"", startIndex + 1);
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
void TileMapLoader::ReadTextureData(const std::string& sentence, intPair chunkPos, int row, std::shared_ptr<dae::Scene> scene)
{

    size_t start = 0;
    for (int j = 0; j < ChunkWidth; ++j)
    {

        size_t indexOfComma = sentence.find_first_of(",", start);
        //for the last texture it's different
        if (j == 15)
        {
            std::string lastNumber = sentence.substr(start, sentence.length() - start);

            int spriteIndexOfLast = std::stoi(lastNumber);
            if (spriteIndexOfLast != 0)
            {
                float2 TexturePos{ (chunkPos.x - StartPos.x) * TileSize + j * TileSize + m_TransformPos.x, (chunkPos.y - StartPos.y) * TileSize + row * TileSize + m_TransformPos.y };
                std::cout << TexturePos.x << ", " << TexturePos.y << '\n';
                int newIndex = spriteIndexOfLast - 1;

                auto TileObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());

                TileObject->GetTransform()->Translate(float(TexturePos.x), float(TexturePos.y));
                std::string test = fileStrings[newIndex];
                // for next line seperate the texturefile to 4 cause we can't split it. have a string with all filenames that are according to the data written
                auto TextureComp = std::shared_ptr<comps::TextureComponent>(new comps::TextureComponent(fileStrings[newIndex], TileSize, TileSize));
                TileObject->AddComponent(TextureComp, ComponentType::TEXTURECOMPONENT);
                scene->Add(TileObject);
            }
           
        }
        else if (indexOfComma != -1)
        {

            std::string last = sentence.substr(start, indexOfComma - start);

            if (last != "")
            {
                int spriteIndex = std::stoi(last);
                if (spriteIndex != 0)
                {
                    float2 texturePos{ (chunkPos.x - StartPos.x) * TileSize + j * TileSize + m_TransformPos.x, (chunkPos.y - StartPos.y) * TileSize + row * TileSize + m_TransformPos.y };
                    std::cout << texturePos.x << ", " << texturePos.y << '\n';
                    int newIndex = spriteIndex - 1;

                    auto TileObject = std::shared_ptr<dae::GameObject>(new dae::GameObject());
                    TileObject->GetTransform()->Translate(float(texturePos.x), float(texturePos.y));
                    std::string test = fileStrings[newIndex];
                    // for next line seperate the texturefile to 4 cause we can't split it. have a string with all filenames that are according to the data written
                    auto TextureComp = std::shared_ptr<comps::TextureComponent>(new comps::TextureComponent(fileStrings[newIndex], TileSize, TileSize));

                    TileObject->AddComponent(TextureComp, ComponentType::TEXTURECOMPONENT);

                    scene->Add(TileObject);
                }
            }

        }
        start = indexOfComma + 1;

    }
}
void TileMapLoader::ReadCollisionData(const std::string& sentence, std::list<std::shared_ptr<rectangle_>>& collision)
{
    //read all the collision
    size_t startIndex = sentence.find_first_of("\"", 0);

    //read ID
    size_t endIndex = sentence.find_first_of("\"", startIndex + 1);


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
    auto scale = TileSize / 16.0f;

    auto rect = std::shared_ptr<rectangle_>(new rectangle_{ XPos * scale + m_TransformPos.x, YPos * scale + m_TransformPos.y, width * scale, height * scale });

    
    collision.push_back(rect);


}



