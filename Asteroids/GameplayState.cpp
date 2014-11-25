#include "GameplayState.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Game.h"

GameplayState::GameplayState(Game* _game)
: GameState(_game), 
currentWave(0), 
timeSinceLastShot(0), 
gameRunning(true), 
hud(&ship, font)
{
}

GameplayState::~GameplayState()
{
}

void GameplayState::createNewWave()
{
	for (int i = 0; i < floor(currentWave * 0.7 * 6); i++)
	{
		asteroids.push_back(std::make_shared<Asteroid>());
	}
	currentWave++;
}

void GameplayState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
		{
			window->close();
		}
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space && timeSinceLastShot > Game::timePerFrame.asSeconds() * 10)
				{
					bullets.push_back(std::make_shared<Bullet>(ship.getPosition(), ship.getDirection()));
					audioManager.playSound(AudioManager::SoundEffect::fire);
					timeSinceLastShot = 0;
				}
		}
	}

}

void GameplayState::update(sf::Time dt)
{
	if (asteroids.empty())
	{
		createNewWave();
		ship.reset();
	}
	for (auto a : asteroids)
	{
		a->update(dt);
	}
	for (auto b : bullets)
	{
		b->update(dt);
	}
	ship.update(dt);
	//if (ship.engineOn())
	//{
	//	audioManager.playSound(AudioManager::SoundEffect::thrust);
	//}
	hud.update();
	timeSinceLastShot += dt.asSeconds();
	handleCollisions();
}

void GameplayState::render()
{
	window->clear();
	for (auto a : asteroids)
	{
		window->draw(*a);
	}
	for (auto b : bullets)
	{
		window->draw(*b);
	}
	window->draw(ship);
	window->draw(hud);
	window->display();
}

void GameplayState::handleCollisions()
{
	for (unsigned i = 0; i < asteroids.size(); i++)
	{
		if (!ship.isRespawning() && asteroids.at(i)->intersect(ship))
		{
			ship.reset();
			ship.decrementLives();
			if (ship.getLives() <= 0)
			{
				game->changeState(Game::States::GAME_OVER, ship.getScore());
				return;
			}
		}
		for (unsigned j = 0; j < bullets.size(); j++)
		{
			if (!(bullets.at(j)->isAlive()))
			{
				bullets.erase(bullets.begin() + j);
			}
			else if (asteroids.size() > i && asteroids.at(i)->intersect(*(bullets.at(j))))
			{
				//Scores update
				switch (asteroids.at(i)->getSize())
				{
				case Asteroid::Size::SMALL:
					ship.updateScore(100);
					audioManager.playSound(AudioManager::SoundEffect::explosionSmall);
					break;
				case Asteroid::Size::MEDIUM:
					ship.updateScore(40);
					audioManager.playSound(AudioManager::SoundEffect::explosionMedium);
					break;
				case Asteroid::Size::BIG:
					audioManager.playSound(AudioManager::SoundEffect::explosionBig);
					ship.updateScore(20);
					break;
				}
				//Asteroids split
				if (asteroids.at(i)->getSize() != Asteroid::Size::SMALL)
				{
					sf::Vector2f speed = asteroids.at(i)->getSpeed();
					sf::Vector2f position = asteroids.at(i)->getPosition();
					asteroids.push_back(std::make_shared<Asteroid>(static_cast<Asteroid::Size>(asteroids.at(i)->getSize() + 1),
						sf::Vector2f{ speed.x * 2, -speed.y * 2 }, position));
					asteroids.push_back(std::make_shared<Asteroid>(static_cast<Asteroid::Size>(asteroids.at(i)->getSize() + 1),
						sf::Vector2f{ -speed.x * 2, speed.y * 2 }, position));
				}
				asteroids.erase(asteroids.begin() + i);
				bullets.erase(bullets.begin() + j);
			}
		}
	}
}