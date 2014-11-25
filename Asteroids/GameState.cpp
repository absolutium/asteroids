#include "GameState.h"
#include <iostream>

const std::string GameState::fontPath = "fonts/Hyperspace Bold.ttf";

GameState::GameState(Game* _game) 
: game(_game), window(_game->getWindow())
{
	if (!font.loadFromFile(fontPath))
	{
		std::cerr << " Error loading font";
	}
}

GameState::~GameState()
{
}

void GameState::centerText(sf::Text& txt, float height)
{
	txt.setPosition(400 - txt.getGlobalBounds().width / 2, height);
}

sf::Text GameState::getText(unsigned size, float height, std::string str, sf::Text::Style style, bool centered)
{
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(size);
	txt.setString(str);
	if (centered)
	{
		centerText(txt, height);
	}
	else
	{
		txt.setPosition(0.f, height);
	}
	txt.setStyle(style);
	return txt;

}