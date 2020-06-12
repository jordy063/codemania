#include "MiniginPCH.h"
#include "EndLevelMenu.h"
#include <fstream>
#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameInfo.h"
#include "Menu.h"

void EndLevelMenu::readDataFromJSON()
{
    //open file
    std::ifstream myfile;
    myfile.open("../Graphics/JSON_GameOverMenu.txt");
    if (myfile.fail())
    {
        throw(std::runtime_error(std::string("could not find JSON file: ") + SDL_GetError()));
    }


    else if (myfile.is_open())
    {
        //read file and set all the parameters according to the language

        //first line is language.

        //skip 2nd line
        //read if the first parameter = language. if not next line
        //else read all parameters
        std::string line;
        int index{};

        while (std::getline(myfile, line))
        {
            switch (index)
            {
            case 0:
                index++;
                break;
            default:
                if (readLanguageParameters(line, m_Language))
                {
                    myfile.close();
                }


                //here we read all parameters

                break;
            }

        }
    }
}

void EndLevelMenu::Initialize()
{
    readDataFromJSON();
    m_pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
    dae::ResourceManager::GetInstance().LoadTexture("../Graphics/title.png");


    FillInTexture(m_pMenuTextures, { 255,255,255 });
    FillInTexture(m_pSelectedMenuTextures, { 0,255,0 });
    FillInTitle({ 255,255,255 });

    
    m_pEndMenuObserver = std::make_shared<EndMenuObserver>(-1);
    dae::InputManager::GetInstance().Register(m_pEndMenuObserver, -1);
}

void EndLevelMenu::Update()
{
   
}

void EndLevelMenu::Render()
{
    auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();



    SDL_RenderClear(renderer);
  
    dae::Renderer::GetInstance().RenderTexture(*m_pTitleTexture, 50, 200.0f);
      
    RenderMenuItems();

    SDL_RenderPresent(renderer);
}

void EndLevelMenu::SetShowMenu(bool showMenu)
{
    UNREFERENCED_PARAMETER(showMenu);
}

void EndLevelMenu::MoveUp()
{
    m_SelectIndex += m_ButtonAmount - 1;
    m_SelectIndex %= m_ButtonAmount;
}

void EndLevelMenu::MoveDown()
{
    m_SelectIndex++;
    m_SelectIndex %= m_ButtonAmount;
}

void EndLevelMenu::Confirm()
{
    if (GameInfo::GetInstance().GetGameState() == GameState::ENDLEVELMENU)
    {
        //get the item by selectindex

        EndLevelMenuItem action = static_cast<EndLevelMenuItem>(m_SelectIndex);

        switch (action)
        {
        case EndLevelMenuItem::PLAYAGAIN:
            GameInfo::GetInstance().SetGameState(RESET);
            break;
        case EndLevelMenuItem::QUIT:
            m_IsQuitCalled = true;
            break;
        default:
            break;
        }
    }
}


bool EndLevelMenu::readLanguageParameters(const std::string& line, const std::string& language)
{
    size_t startIndex = line.find_first_of("\"", 0);

    //read ID
    size_t endIndex = line.find_first_of("\"", startIndex + 1);

    std::string readLanguage = line.substr(startIndex + 1, endIndex - startIndex - 1);
    if (readLanguage == language)
    {
        for (int i{}; i <= int(EndLevelMenuItem::QUIT); ++i)
        {
            startIndex = endIndex + 1;

            //read first part
            startIndex = line.find_first_of("\"", startIndex);
            endIndex = line.find_first_of("\"", startIndex + 1);
            std::string name = line.substr(startIndex + 1, endIndex - startIndex - 1);

            //read 2nd part
            startIndex = endIndex + 1;

            startIndex = line.find_first_of("\"", startIndex);
            endIndex = line.find_first_of("\"", startIndex + 1);
            std::string title = line.substr(startIndex + 1, endIndex - startIndex - 1);

            m_MenuMap[static_cast <EndLevelMenuItem>(i)] = title;
        }

        return true;
    }
    return false;
}

void EndLevelMenu::FillInTexture(std::map<EndLevelMenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures, SDL_Color color)
{
    for (std::pair<EndLevelMenuItem, std::string> menuItem : m_MenuMap)
    {
        const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), menuItem.second.c_str(), color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
        }
        auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }
        SDL_FreeSurface(surf);

        menuTextures[menuItem.first] = std::make_shared<dae::Texture2D>(texture);

    }
}

void EndLevelMenu::FillInTitle(SDL_Color color)
{
    std::string title{ "you actually completed it. well done!" };

    const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), title.c_str(), color);
    if (surf == nullptr)
    {
        throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
    }
    auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
    if (texture == nullptr)
    {
        throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
    }
    SDL_FreeSurface(surf);

    m_pTitleTexture = std::make_shared<dae::Texture2D>(texture);
    
}

void EndLevelMenu::RenderMenuItems()
{
    int counter{};

    //depending on which button is selected we render a different texture
    for (int i{}; i < m_ButtonAmount; ++i)
    {
        if (counter != m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pMenuTextures[static_cast<EndLevelMenuItem>(i)], 200, 32.0f * counter + 300.0f);

        }
        counter++;
    }

    counter = 0;


    for (int i{}; i < m_ButtonAmount; ++i)
    {
        if (counter == m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pSelectedMenuTextures[static_cast<EndLevelMenuItem>(i)], 200, 32.0f * counter + 300.0f);
        }
        counter++;
    }
}
