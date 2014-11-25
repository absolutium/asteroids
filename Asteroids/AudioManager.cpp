#include "AudioManager.h"
#include <iostream>
#include <memory>
#include <algorithm>

AudioManager::AudioManager()
{
	soundBuffers.emplace(SoundEffect::fire, loadSoundBuffer("sounds/fire.wav"));
	//soundBuffers.emplace(SoundEffect::thrust, loadSoundBuffer("sounds/thrust.wav"));
	soundBuffers.emplace(SoundEffect::explosionBig, loadSoundBuffer("sounds/bangBig.wav"));
	soundBuffers.emplace(SoundEffect::explosionMedium, loadSoundBuffer("sounds/bangMedium.wav"));
	soundBuffers.emplace(SoundEffect::explosionSmall, loadSoundBuffer("sounds/bangSmall.wav"));
}


AudioManager::~AudioManager()
{
}

void AudioManager::playSound(SoundEffect se)
{
	sounds.remove_if(
		[] (const sf::Sound& s) 
		{
			return s.getStatus() == sf::Sound::Stopped;
		}
	);
	sf::Sound s(soundBuffers[se]);
	sounds.push_back(s);
	sounds.back().play();
}


sf::SoundBuffer AudioManager::loadSoundBuffer(std::string filename)
{
	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
	if (!buffer->loadFromFile(filename))
	{
		std::cerr << "Couln't load sound";
	}
	return *buffer;
}