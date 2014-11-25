#pragma once
#include <memory>
#include "GameState.h"
#include "AudioManager.h"
#include "Ship.h"
#include "Hud.h"
#include "Asteroid.h"
#include "Bullet.h"

class GameplayState : public GameState
{
public:
	GameplayState(Game* _game);
	virtual ~GameplayState();

	virtual void update(sf::Time dt) override;
	virtual void render() override;
	virtual void handleEvents() override;

private:
	bool gameRunning;
	int currentWave;
	//prevents the ship from constant firing
	float timeSinceLastShot;

	Ship ship;
	Hud hud;
	std::vector<std::shared_ptr<Asteroid>> asteroids;
	std::vector<std::shared_ptr<Bullet>> bullets;

	AudioManager audioManager;

	void handleCollisions();
	void createNewWave();
};

