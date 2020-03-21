#include "MiniginPCH.h"
#include "SoundManager.h"




void SoundManager::Init()
{
	//audio device
	SDL_AudioSpec want, have;


	SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
	want.freq = 48000;
	want.format = AUDIO_F32;
	want.channels = 2;
	want.samples = 4096;
	want.callback = NULL; /* you wrote this function elsewhere -- see SDL_AudioSpec for details */

	

	//audio device
	m_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (m_dev == 0) {
		SDL_Log("Failed to open audio: %s", SDL_GetError());
	}
	else {
		if (have.format != want.format) { /* we let this one thing change. */
			SDL_Log("We didn't get Float32 audio format.");
		}
		SDL_PauseAudioDevice(m_dev, 0); /* start audio playing. */
	}


	

	/* Load the WAV */
	
}

bool SoundManager::LoadSound(char* filename) {
	//load sounds
	Sound sound;

	if (SDL_LoadWAV(filename, &sound.wav_spec, &sound.wav_buffer, &sound.wav_length) == NULL) {
		fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
		return false;
	}
	else {
		/* Do stuff with the WAV data, and then... */
		m_soundmap[filename] = sound;
		return true;
	}
}


bool SoundManager::PlaySound(char* filename) {
	if (m_soundmap.count(filename) == 0) {
		if (!LoadSound(filename))
		{
			return false;
		}
	}
	auto sound = m_soundmap[filename];
	SDL_QueueAudio(m_dev, sound.wav_buffer, sound.wav_length);
	return true;
}