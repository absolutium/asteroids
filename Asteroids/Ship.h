#pragma once
#include "Entity.h"

class Ship : public Entity
{
public:
	Ship();
	~Ship();

	/**
		Resets the ship to the starting position in the middle of the screen. It does not decrement the
		remaining number of lives.
		Should be called after colliding with an asteroid and at the start of a new wave.
	*/
	void reset();
	void decrementLives() { lives--; }

	int getLives() const { return lives; }
	sf::Vector2f getPosition() const { return shape.getPosition(); }
	float getDirection() const { return direction; }
	unsigned int getScore() { return score; }
	bool engineOn(){ return acceleration > 0; }

	bool isRespawning();
	void updateScore(int sc) { score += sc; }
	virtual void update(sf::Time dt) override;

private:
	sf::ConvexShape shape;
	static const int numberOfLives = 3;
	// in seconds
	const float respawnTime = 2.f;
	float timeSinceRespawn;
	// angle in radians
	float direction;
	float acceleration;
	int lives;
	unsigned score;
};