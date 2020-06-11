#include "MiniginPCH.h"
#include "GameOverMenu.h"
#include <fstream>
#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameInfo.h"

void GameOverMenu::readDataFromJSON()
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

void GameOverMenu::Initialize()
{
    readDataFromJSON();
    m_pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
    dae::ResourceManager::GetInstance().LoadTexture("../Graphics/title.png");


    FillInTexture(m_pMenuTextures, { 255,255,255 });
    FillInTexture(m_pSelectedMenuTextures, { 0,255,0 });
    FillInTitle({ 255,255,255 });

    //add an observer for this menu

    m_pGameOverMenuObserver = std::make_shared<GameOverMenuObserver>(-1);
    dae::InputManager::GetInstance().Register(m_pGameOverMenuObserver, -1);
}

void GameOverMenu::Update()
{
}

void GameOverMenu::Render()
{
    auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();



    SDL_RenderClear(renderer);
   
    //here we also draw game over or winner with the player number depending on the gamemode
    switch (GameInfo::GetInstance().GetGameMode())
    {
    case GameMode::VERSUS:
        //check which player won and return de player number
        if (m_DeathId == 0)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pTitleTextures[2], 200, 200.0f);
        }
        else
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pTitleTextures[1], 200, 200.0f);
        }
        break;
    default:
        //render titles[0]
        dae::Renderer::GetInstance().RenderTexture(*m_pTitleTextures[0], 75, 200.0f);
        break;
    }


    RenderMenuItems();


    SDL_RenderPresent(renderer);
}

void GameOverMenu::SetShowMenu(bool showMenu)
{
	UNREFERENCED_PARAMETER(showMenu);

}

void GameOverMenu::MoveUp()
{
    m_SelectIndex += m_ButtonAmount - 1;
    m_SelectIndex %= m_ButtonAmount;
}

void GameOverMenu::MoveDown()
{
    m_SelectIndex++;
    m_SelectIndex %= m_ButtonAmount;
}

void GameOverMenu::Confirm()
{
    if (GameInfo::GetInstance().GetGameState() == GameState::GAMEOVERMENU)
    {
        //get the item by selectindex

        GameOverMenuItem action = static_cast<GameOverMenuItem>(m_SelectIndex);

        switch (action)
        {
        case GameOverMenuItem::PLAYAGAIN:
            GameInfo::GetInstance().SetGameState(RESET);
            break;
        case GameOverMenuItem::QUIT:
            m_IsQuitCalled = true;
            break;
        default:
            break;
        }
    }
}

void GameOverMenu::RegisterDeath(int id)
{
    if (m_DeathId == -1)
    {
        m_DeathId = id;
    }
}

bool GameOverMenu::readLanguageParameters(const std::string& line, const std::string& language)
{
    size_t startIndex = line.find_first_of("\"", 0);

    //read ID
    size_t endIndex = line.find_first_of("\"", startIndex + 1);

    std::string readLanguage = line.substr(startIndex + 1, endIndex - startIndex - 1);
    if (readLanguage == language)
    {
        for (int i{}; i <= int(GameOverMenuItem::QUIT); ++i)
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

            m_MenuMap[static_cast <GameOverMenuItem>(i)] = title;
        }

        return true;
    }
    return false;
}

void GameOverMenu::FillInTexture(std::map<GameOverMenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures, SDL_Color color)
{
    for (std::pair<GameOverMenuItem, std::string> menuItem : m_MenuMap)
    {
        //const SDL_Color color = { 255,255,255 }; // only white text is supported now
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

void GameOverMenu::FillInTitle( SDL_Color color)
{
    std::vector<std::string> titles{};
    
    titles.push_back("You died. better luck next time");
    titles.push_back("player 1 wins");
    titles.push_back( "player 2 wins");

    for (std::string title : titles)
    {
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

        m_pTitleTextures.push_back(std::make_shared<dae::Texture2D>(texture));
    }
}



void GameOverMenu::RenderMenuItems()
{
    int counter{};

    for (int i{}; i < m_ButtonAmount; ++i)
    {
        if (counter != m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pMenuTextures[static_cast<GameOverMenuItem>(i)], 200, 32.0f * counter + 300.0f);

        }
        counter++;
    }

    counter = 0;


    for (int i{}; i < m_ButtonAmount; ++i)
    {
        if (counter == m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pSelectedMenuTextures[static_cast<GameOverMenuItem>(i)], 200, 32.0f * counter + 300.0f);
        }
        counter++;
    }

}


