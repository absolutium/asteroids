#pragma once
#include "GameState.h"

class HighscoresState : public GameState
{
public:
	HighscoresState(Game* _game);
	virtual ~HighscoresState();

	virtual void handleEvents() override;
	virtual void update(sf::Time dt) override {};
	virtual void render() override;

private:
	sf::Text title;
	sf::Text scores;
	sf::Text backButton;

	void getScores();
};