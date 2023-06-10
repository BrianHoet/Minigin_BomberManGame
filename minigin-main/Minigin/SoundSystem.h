#pragma once
#include <map>
#include <SDL_mixer.h>

#include "BaseSoundSystem.h"

namespace dae
{

	class SoundSystem final : public BaseSoundSystem
	{
	public:

		SoundSystem();

		~SoundSystem() = default;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;

		void playSound(const sound_id id, const float volume) override;
		void playMusic(const sound_id id, const float volume) override;
		void Load(const sound_id id, const std::string& path) override;

	private:

		enum SoundState
		{
			SoundPlay,
			SoundLoaded
		};

		std::map<sound_id, Mix_Chunk*> m_Sound{};

	};
}
