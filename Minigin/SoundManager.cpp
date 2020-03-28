#include "MiniginPCH.h"
#include "SoundManager.h"




void SoundManager::Init()
{
	//audio device
	//SDL_AudioSpec want, have;
	//SDL_Init(SDL_INIT_AUDIO);

	//SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
	//want.freq = 48000;
	//want.format = AUDIO_F32;
	//want.channels = 2;
	//want.samples = 4096;
	//want.callback = NULL; /* you wrote this function elsewhere -- see SDL_AudioSpec for details */

	//

	////audio device
	//m_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	//if (m_dev == 0) {
	//	SDL_Log("Failed to open audio: %s", SDL_GetError());
	//}
	//else {
	//	if (have.format != want.format) { /* we let this one thing change. */
	//		SDL_Log("We didn't get Float32 audio format.");
	//	}
	//	SDL_PauseAudioDevice(m_dev, 0); /* start audio playing. */
	//}
	
	std::string filename = "../Sounds/drumloop.wav";
	LoadSound(filename);

	/* Load the WAV */
	
}

bool SoundManager::LoadSound(const std::string filename) {
	//load sounds
	//Sound sound;

	//if (SDL_LoadWAV(filename.c_str(), &sound.wav_spec, &sound.wav_buffer, &sound.wav_length) == NULL) {
	//	fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
	//	return false;
	//}
	//else {
	//	/* Do stuff with the WAV data, and then... */
	//	m_soundmap[filename] = sound;
	//	return true;
	//}


	

	SDL_AudioSpec wavSpec;
	UINT8* wavStart;
	UINT32 wavLength;

	if (SDL_LoadWAV(filename.c_str(), &wavSpec, &wavStart, &wavLength) == NULL) {
		fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
		return false;
	}

	AudioData audio;
	audio.pos = wavStart;
	audio.length = wavLength;
	//wavSpec.callback = MyAudioCallBack;
	wavSpec.userdata = &audio;
	m_dev = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	SDL_QueueAudio(m_dev,&wavSpec, wavLength);

	if (m_dev == 0)
	{
		fprintf(stderr, "audiodevice = null: %s\n", SDL_GetError());
		return false;
	}
	SDL_PauseAudioDevice(m_dev, 0);

	while (audio.length > 0)
	{
		SDL_Delay(100);
	}
	SDL_CloseAudioDevice(m_dev);
	SDL_FreeWAV(wavStart);
	return true;

}


bool SoundManager::PlaySound(const std::string filename) {
	if (m_soundmap.count(filename) == 0) {
		if (!LoadSound(filename))
		{
			return false;
		}
	}
	auto sound = m_soundmap[filename];
	SDL_QueueAudio(m_dev, sound.wav_buffer, sound.wav_length);

	SDL_Delay(1000);
	return true;
}

void MyAudioCallBack(void* userData, UINT* stream, int streamLength)
{
	AudioData* audio = (AudioData*)userData;

	if (audio->length == 0)
	{
		return;
	}

	UINT32 length = (UINT32)streamLength;
	length = (length > audio->length ? audio->length : length);

	SDL_memcpy(stream, audio->pos, length);

	audio->pos += length;
	audio->length -= length;
}