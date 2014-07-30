#ifndef PERSON_HPP
#define PERSON_HPP

#include <cmath>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Engine/MapPortal.hpp"

class Person : public sf::CircleShape
{
public:
	Person(sf::Vector2f  spawn, MapComponent* goal=nullptr);
	Person(MapComponent* spawn, MapComponent* goal=nullptr);

	void addWaypoint(sf::Vector2f wp);

	/**
	 * @brief move
	 * @param elapsed
	 * @return last waypoint reached?
	 */
	bool move(sf::Time elapsed);

private:
	std::queue<sf::Vector2f> _waypoint;

	MapComponent* _goal;

	float _speed;
};

#endif // PERSON_HPP
