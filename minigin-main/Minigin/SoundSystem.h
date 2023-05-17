#pragma once
#include <iostream>
#include <vector>

class AudioImpl;

class Audio
{
public:
	Audio();
	virtual ~Audio();
	void addSound(const std::string& soundName);
	void playSound(int soundID);
	void stopSound(int soundID);
	void stopAllSounds();

private:
	std::unique_ptr<AudioImpl> audioImpl;
};

class SoundSystemLocator
{
public:
	static void initialize() {}

	static Audio& getAudio() { return *instance; }

	static void provide(std::shared_ptr<Audio> service)
	{
		instance = service;
	}

private:
	static std::shared_ptr<Audio> instance;
};