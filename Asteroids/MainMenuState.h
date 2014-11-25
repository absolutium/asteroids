#pragma once
#include <memory>
#include "GameState.h"
#include "Asteroid.h"

class MainMenuState : public GameState
{
public:
	MainMenuState(Game *_game);
	virtual ~MainMenuState();

	virtual void handleEvents() override;
	virtual void update(sf::Time dt) override;
	virtual void render() override;

private:
	sf::Text title;
	sf::Text playButton;
	sf::Text highscoreButton;

	std::vector<std::shared_ptr<Asteroid>> asteroids;
};

