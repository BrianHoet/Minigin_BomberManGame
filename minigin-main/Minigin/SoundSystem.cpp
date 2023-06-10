#include "SoundSystem.h"
#include <cassert>
#include "ResourceManager.h"

dae::SoundSystem::SoundSystem()
{
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
}

void dae::SoundSystem::playSound(const dae::sound_id id, const float volume)
{
	auto playchunk = m_Sound.at(id);

	if(playchunk == nullptr)
		return;
	
	auto channel = Mix_PlayChannel(-1, playchunk, 0);
	Mix_Volume(channel, static_cast<int>(volume));

}

void dae::SoundSystem::playMusic(const sound_id id, const float volume)
{
	auto playchunk = m_Sound.at(id);

	if (playchunk == nullptr)
		return;

	auto channel = Mix_PlayChannel(1, playchunk, -1);
	Mix_Volume(channel, static_cast<int>(volume));
}

void dae::SoundSystem::Load(const dae::sound_id id, const std::string& path)
{
	
	auto datapath = ResourceManager::GetInstance().ReturnDataPath() + "SoundEffects/";
	auto fullpath = datapath + path;
	auto chunk = Mix_LoadWAV(fullpath.c_str());
	m_Sound.emplace(id, chunk);
}
    