#pragma once
class Audio
{
public:
	virtual ~Audio() = default;
	virtual void PlaySound(int id) = 0;
	virtual void StopSound(int id) = 0;
	virtual void StopAllSounds() = 0;
};
class ServiceLocator
{
public:
	static Audio* GetAudio() { return m_AudioService; } ;
	static void RegisterAudioService(Audio* service) { m_AudioService = service; }

private:
	static Audio* m_AudioService;
};




