#include "HighscoresState.h"
#include <SFML\Network.hpp>
#include <iostream>

HighscoresState::HighscoresState(Game *_game)
: GameState(_game),
title(getText(45,25.f,"high scores")),
backButton(getText(30, 500.f, "back")),
scores(getText(25, 150.f, "", sf::Text::Style::Regular))
{
	getScores();
}


HighscoresState::~HighscoresState()
{
}

void HighscoresState::render()
{
	window->clear();
	window->draw(title);
	window->draw(scores);
	window->draw(backButton);
	window->display();
}

void HighscoresState::getScores()
{
	sf::Http http(url);
	sf::Http::Request req("/display.php", sf::Http::Request::Get);
	sf::Http::Response resp = http.sendRequest(req);
	if (resp.getStatus() == sf::Http::Response::Ok)
	{
		scores.setString(resp.getBody());
	}
	else
	{
		scores.setString("No internet connection!");
	}
	centerText(scores, 150.f);
}

void HighscoresState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
		{
			window->close();
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				game->changeState(Game::States::MAIN_MENU);
				break;
			}
		}
	}

}