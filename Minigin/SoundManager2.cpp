#include "MiniginPCH.h"
#include "SoundManager2.h"
#include "SDL_mixer.h"
#include <string>

// Initialize our static variables
SoundManager2::AudioState SoundManager2::currentState = FAULT;


void SoundManager2::Init()
{
    if (SDL_Init(SDL_INIT_AUDIO) != -1)
    {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            std::cerr << "Error initializing audio device...\n";
            currentState = FAULT;
        }
        else
        {
            currentState = WAITING;
        }
    }
    else
    {
        std::cerr << "Error initializing SDL audio subsystem...\n";
        currentState = FAULT;
    }
}

void SoundManager2::playMusic(const std::string& fileName)
{
    if (m_MusicMap.count(fileName) == 0)
    {
        auto music = Mix_LoadMUS(fileName.c_str());

        if (music == NULL)
        {
            std::cerr << "Error loading music file: " << fileName << std::endl;
        }
        else
        {
            m_MusicMap[fileName] = music;
            //Play music
           
        }
    }

    if (Mix_PlayingMusic() == 0)
    {

        Mix_PlayMusic(m_MusicMap[fileName], -1);
        currentState = PLAYING;

    }
    else
    {
        // If music is playing, pause it
        this->pauseMusic();
    }

}

void SoundManager2::pauseMusic()
{
    if (currentState != FAULT)
    {
        // If music is playing, handle the pause request
        if (Mix_PlayingMusic() == 1)
        {
            if (Mix_PausedMusic() == 1)
            {
                // If we receive a pause request and the music is already paused, resume it.
                Mix_ResumeMusic();
                currentState = PLAYING;
            }
            else
            {
                // Otherwise, pause the music
                Mix_PauseMusic();
                currentState = PAUSED;
            }
        }
    }
}

void SoundManager2::stopMusic()
{
    if (currentState != FAULT)
    {
        Mix_HaltMusic();
        currentState = STOPPED;
    }
}

void SoundManager2::playEffect(const std::string& fileName)
{
    if (m_MusicMap.count(fileName) == 0)
    {
        auto effect = Mix_LoadWAV(fileName.c_str());

        if (effect == NULL)
        {
            std::cerr << "Error loading music file: " << fileName << std::endl;
        }
        else
        {
            m_EffectsMap[fileName] = effect;
        }

    }

        Mix_PlayChannel(-1, m_EffectsMap[fileName], 0);
    

}