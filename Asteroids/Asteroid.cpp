#include "Asteroid.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdlib>

std::map<Asteroid::Size, int> Asteroid::radiuses = { { BIG, 55 }, { MEDIUM, 35 }, { SMALL, 15 } };

Asteroid::Asteroid()
:size(BIG), shape(new sf::ConvexShape())
{
	shape->setPosition(static_cast<float>(rand() % 801), static_cast<float>(rand() % 601));
	shape->setFillColor(sf::Color::Black);
	shape->setOutlineColor(sf::Color::White);
	shape->setOutlineThickness(1);

	// Velocity is always the same and is equal to the value of the initialVelocity constant. The x component 
	// of the speed vector is randomly generated, and the y component is the complement to the initialVelocity. 
	// The sign of y is randomly generated.
	float speedx = static_cast<float>(rand() % 40 - initialVelocity);
	int sign = rand() % 2;
	if (sign == 0) sign = -1;
	float speedy = sign * (initialVelocity - abs(speedx));
	speed = sf::Vector2f(speedx, speedy);
	generateShape();
	ashape = shape;
}

Asteroid::Asteroid(Size _size, sf::Vector2f _speed, sf::Vector2f _position)
:size(_size), shape(new sf::ConvexShape())
{
	shape->setPosition(_position);
	shape->setFillColor(sf::Color::Black);
	shape->setOutlineColor(sf::Color::White);
	shape->setOutlineThickness(1);
	speed = _speed;
	generateShape();
	ashape = shape;
}

Asteroid::~Asteroid()
{
	delete shape;
}

void Asteroid::update(sf::Time dt)
{
	shape->move(speed.x * dt.asSeconds(), speed.y * dt.asSeconds());
	sf::FloatRect bounds = shape->getGlobalBounds();
	if (bounds.left + bounds.width < 0)
	{
		shape->move(800.f + bounds.width, 0.f);
	}
	else if (bounds.left - bounds.width > 800)
	{
		shape->move(-800.f - bounds.width, 0.f);
	}
	else if (bounds.top - bounds.height < 0)
	{
		shape->move(0.f, 600.f + bounds.height);
	}
	else if (bounds.top > 600)
	{
		shape->move(0.f, -600.f - bounds.height);
	}
}

void Asteroid::generateShape()
{
	std::vector<float> points;
	shape->setPointCount(numberOfSides);
	for (int i = 0; i < numberOfSides; i++)
	{
		points.push_back(static_cast<float>(rand() * 2 * M_PI / (RAND_MAX + 1)));
	}
	std::sort(points.begin(), points.end());
	for (int i = 0; i < numberOfSides; i++)
	{
		shape->setPoint(i, sf::Vector2f(radiuses.at(size) * sin(points.at(i)), 
			radiuses.at(size) * cos(points.at(i))));
	}
}