#include "SoundSystemEffects.h"
#include <cassert>
#include "ResourceManager.h"

dae::SoundSystemEffects::SoundSystemEffects()
{
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
}

void dae::SoundSystemEffects::play(const dae::sound_id id, const float volume)
{
	auto playchunk = m_Sound.at(id);

	assert(playchunk == nullptr);
	
	auto channel = Mix_PlayChannel(-1, playchunk, 0);
	Mix_Volume(channel, static_cast<int>(volume));

}

void dae::SoundSystemEffects::Load(const dae::sound_id id, const std::string& path)
{
	
	auto datapath = ResourceManager::GetInstance().ReturnDataPath() + "SoundEffects/";
	auto fullpath = datapath + path;
	auto chunk = Mix_LoadWAV(fullpath.c_str());
	m_Sound.emplace(id, chunk);
}

void dae::SoundSystemEffects::UpdateSound()
{
}
