#define OLC_SOUNDWAVE

#include "Audio.h"

void Audio::start()
{
	we.InitialiseAudio();
}

void Audio::addSound(std::string name, std::string path)
{
	sounds[name] = olc::sound::Wave(path);
}

void Audio::playSound(std::string name, bool loop)
{
	olc::sound::PlayingWave pw = we.PlayWaveform(&sounds[name], loop);
}

//void Audio::fadeSoundOut(std::string name)
//{
//	we.StopWaveform(sounds[name]);
//}

Audio aud;

olc::sound::WaveEngine Audio::we;
std::map<std::string, olc::sound::Wave> Audio::sounds;
