#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	Entity();
	virtual ~Entity();

	/**
		Generic collision detection method, works for any convex shapes
		Uses Separating Axis Theorem
	*/
	bool intersect(const Entity& e) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::Time dt) = 0;

protected:
	sf::Vector2f speed;
	sf::Shape *ashape;

private:
	//auxiliary methods for collision detection
	static float dotProduct(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
	static sf::Vector2f unitVector(const sf::Vector2f& vector);
	static sf::Vector2f perpendicularVector(const sf::Vector2f& vector);
	static sf::Vector2f getPoint(const sf::Shape& shape, unsigned int index);
	static sf::Vector2f projectShapeOn(const sf::Shape& shape, const sf::Vector2f& axis);
	static bool existsSeparatingAxisForFirst(const sf::Shape& shape_1, const sf::Shape& shape_2);
};