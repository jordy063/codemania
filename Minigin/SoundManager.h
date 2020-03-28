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

struct AudioData {
	Uint32 length;
	Uint8* pos;
};

class SoundManager final : public dae::Singleton < SoundManager>
{
public:
	void Init();
	bool PlaySound(const std::string filename);

private:
	std::vector<SDL_AudioSpec*> m_Playlist;
	std::map<std::string, Sound> m_soundmap;
	SDL_AudioDeviceID m_dev;
	bool LoadSound(const std::string filename);
};


