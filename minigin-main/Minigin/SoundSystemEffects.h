#pragma once
#include <map>
#include <SDL_mixer.h>

#include "BaseSoundSystem.h"

namespace dae
{

	class SoundSystemEffects final : public BaseSoundSystem
	{
	public:

		SoundSystemEffects();

		~SoundSystemEffects() = default;
		SoundSystemEffects(const SoundSystemEffects& other) = delete;
		SoundSystemEffects(SoundSystemEffects&& other) = delete;
		SoundSystemEffects& operator=(const SoundSystemEffects& other) = delete;
		SoundSystemEffects& operator=(SoundSystemEffects&& other) = delete;

		void play(const sound_id id, const float volume) override;
		void Load(const sound_id id, const std::string& path) override;
		void UpdateSound();

	private:

		enum SoundState
		{
			SoundPlay,
			SoundLoaded
		};

		std::map<sound_id, Mix_Chunk*> m_Sound{};


	};
}
