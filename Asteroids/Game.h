#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class GameState;

// Main class, works as a state manager
class Game
{
public:
	enum class States {MAIN_MENU, HIGHSCORES, GAMEPLAY, GAME_OVER};
	
	Game();
	~Game();

	sf::RenderWindow* getWindow() { return &window; }

	// Main game loop
	void run();
	static const sf::Time timePerFrame;
	void changeState(States nextState, unsigned score = 0);

private:
	bool gameRunning;
	sf::RenderWindow window;
	
	GameState* currentState;

	void handleEvents();
	void update(sf::Time dt);
	void render();
	void gameOver();
};