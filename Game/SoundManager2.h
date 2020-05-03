#pragma once
#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
#include "Singleton.h"
#include <map>


 class SoundManager2 final:public dae::Singleton< SoundManager2>
 {
 public:

     void Init();    

     void playMusic(const std::string& fileName);
     void pauseMusic();
     void stopMusic();
     void playEffect(const std::string& fileName);

     bool isPaused() const {return currentState == PAUSED;}
     bool isStopped() const {return currentState == STOPPED;}
     bool isPlaying() const { return currentState == PLAYING;}

 private:

     enum AudioState
     {
         FAULT,
         WAITING,
         PAUSED,
         STOPPED,
         PLAYING
     };
     static AudioState currentState;

     std::map<std::string, Mix_Music*> m_MusicMap;
     std::map<std::string, Mix_Chunk*> m_EffectsMap;
 };
