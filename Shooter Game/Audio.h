#pragma once

#include "olcSoundWaveEngine.h"
#include <map>

class Audio
{
private:
	static olc::sound::WaveEngine we;
	static std::map<std::string, olc::sound::Wave> sounds;

public:
	static void start();

	static void addSound(std::string name, std::string path);
	static void playSound(std::string name, bool loop = false);
	//static void fadeSoundOut(std::string name);
};

extern Audio aud;
