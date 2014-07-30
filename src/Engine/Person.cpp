#include "Engine/Person.hpp"

Person::Person(sf::Vector2f spawn, MapComponent* goal) :
	_goal(goal),
	_speed(50.0f)
{
	setRadius(12);
	setPosition(spawn-sf::Vector2f(getRadius(),getRadius()));
	setFillColor(sf::Color::Red);
}

Person::Person(MapComponent* spawn, MapComponent* goal) :
	Person(spawn->getCenter(),goal)
{
}

void Person::addWaypoint(sf::Vector2f wp)
{
	_waypoint.push(wp);
}

bool Person::move(sf::Time elapsed)
{
	if (_waypoint.empty())
	{
		return true;
	}
	sf::Vector2f direction = _waypoint.front()-getPosition();
	float dist = sqrt(std::pow(direction.x,2)+(std::pow(direction.y,2)));
	float step = elapsed.asSeconds()*_speed;
	if (step > dist)
	{
		_waypoint.pop();
	}
	direction.x*=step/dist;
	direction.y*=step/dist;
	sf::CircleShape::move(direction);
	return false;
}
