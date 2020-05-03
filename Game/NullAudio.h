#pragma once
#include "Audio.h"

class NullAudio final : public Audio
{
public:
	void PlaySound(int id) override {};
	void StopSound(int id) override {};
	void StopAllSounds() override {};
};

class ServiceLocator
{
public:
	static void Init() { m_AudioService = &m_DefaultAudioService; }
	static Audio& GetAudio() { return *m_AudioService; };
	static void RegisterAudioService(Audio* service) 
	{
		m_AudioService = (service == nullptr) ? &m_DefaultAudioService : service; 
	}

private:
	static Audio* m_AudioService;
	static NullAudio m_DefaultAudioService;
};
