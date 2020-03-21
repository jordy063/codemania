#pragma once
#include "SDL.h"
#include "Singleton.h"
#include <vector>
#include <map>


struct Sound {
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8* wav_buffer;
};

class SoundManager final : public dae::Singleton < SoundManager>
{
public:
	void Init();
	bool PlaySound(char* filename);

private:
	std::vector<SDL_AudioSpec*> m_Playlist;
	std::map<char*, Sound> m_soundmap;
	SDL_AudioDeviceID m_dev;
	bool LoadSound(char* filename);
};

