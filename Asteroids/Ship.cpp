#define _USE_MATH_DEFINES

#include "Ship.h"
#include <math.h>
#include <iostream>

Ship::Ship()
: lives(numberOfLives), acceleration(0), timeSinceRespawn(0.f), score(0)
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(-5.f, 20.f));
	shape.setPoint(2, sf::Vector2f(5.f, 20.f));
	shape.setOrigin(0, 20 * 2/3);
	shape.setPosition(400, 290);
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1);
	ashape = &shape;
	speed.x = 0;
	speed.y = 0;
}

Ship::~Ship()
{
}

void Ship::update(sf::Time dt)
{
	if (isRespawning())
	{
		shape.setOutlineThickness(0.2f);
	}
	else
	{
		shape.setOutlineThickness(1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		acceleration = 130.f * dt.asSeconds();
		speed.x -= sin(direction) * acceleration;
		speed.y += cos(direction) * acceleration;
	}
	else
	{
		acceleration = 0;
		speed.x *= 59.f * dt.asSeconds();
		speed.y *= 59.f * dt.asSeconds();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		shape.rotate(-200.f * dt.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		shape.rotate(200.f * dt.asSeconds());
	}
	sf::Vector2f pos = shape.getPosition();
	direction = static_cast<float>(shape.getRotation() * M_PI / 180 - M_PI);
	shape.move(speed * dt.asSeconds());
	if (pos.x < 0)
	{
		shape.setPosition(800, pos.y);
	}
	else if (pos.x > 800)
	{
		shape.setPosition(0, pos.y);
	}
	else if (pos.y < 0)
	{
		shape.setPosition(pos.x, 600);
	}
	else if (pos.y > 600)
	{
		shape.setPosition(pos.x, 0);
	}
	timeSinceRespawn += dt.asSeconds();
}

void Ship::reset()
{
	shape.setPosition(400, 290);
	shape.setRotation(0);
	speed.x = 0;
	speed.y = 0;
	acceleration = 0;
	timeSinceRespawn = 0.f;
}

bool Ship::isRespawning()
{
	if (timeSinceRespawn < respawnTime) return true;
	else return false;
}