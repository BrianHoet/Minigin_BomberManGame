#pragma once
#include <string>

namespace dae
{

	using sound_id = unsigned short;

	class BaseSoundSystem
	{
	public:
		BaseSoundSystem() = default;
		virtual ~BaseSoundSystem() = default;

		virtual void playSound(const sound_id id, const float volume) = 0;
		virtual void playMusic(const sound_id id, const float volume) = 0;
		virtual void Load(const sound_id id, const std::string& path) = 0;
	};

}

