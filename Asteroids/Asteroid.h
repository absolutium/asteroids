#pragma once
#define _USE_MATH_DEFINES
#include "Entity.h"

class Asteroid : public Entity
{
public:
	enum Size {BIG, MEDIUM, SMALL};
	
	Asteroid();
	Asteroid(Size _size, sf::Vector2f _speed, sf::Vector2f _position);
	~Asteroid();

	Size getSize() const { return size; }
	sf::Vector2f getPosition() const { return shape->getPosition(); }
	sf::Vector2f getSpeed() const { return speed; }
	
	virtual void update(sf::Time dt) override;

private:
	sf::ConvexShape *shape;
	Size size;
	static const int numberOfSides = 10;
	//Initial velocity of a big asteroid
	static const int initialVelocity = 40;
	//Radiuses of the corrensponding circumscribed circles
	static std::map<Size, int> radiuses;

	/**
		Generates random shape of an asteroid
		Asteroid is a cyclic polygon with the circumradius specified by the size value and the
		number of sides specified by the numberOfSides constant
	*/
	void generateShape();
};