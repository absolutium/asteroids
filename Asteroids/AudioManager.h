#pragma once
#include <unordered_map>
#include <queue>
#include <SFML\Audio.hpp>

class AudioManager
{
public:
	enum SoundEffect{ fire, thrust, explosionBig, explosionMedium, explosionSmall };

	AudioManager();
	~AudioManager();

	void playSound(SoundEffect se);
private:
	std::unordered_map<SoundEffect, sf::SoundBuffer> soundBuffers;
	std::list<sf::Sound> sounds;

	sf::SoundBuffer loadSoundBuffer(std::string filename);
};

