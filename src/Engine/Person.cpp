#include "Engine/Person.hpp"

Person::Person(const MapComponent* spawn, const MapComponent* goal) :
	_goal(goal),
	_speed(50.0f)
{
	setRadius(12);
	setPosition(spawn->getCenter()-sf::Vector2f(getRadius(),getRadius()));
	setFillColor(sf::Color::Red);

	_checkpoint.push(spawn->getDirectionTo(goal));
}

bool Person::move(sf::Time elapsed)
{
	if (_checkpoint.empty())
	{
		return true;
	}
	sf::Vector2f direction	= _checkpoint.front()->getCenter()
							- getPosition()
							- sf::Vector2f(getRadius(),getRadius());
	float dist = sqrt(std::pow(direction.x,2)+(std::pow(direction.y,2)));
	float step = elapsed.asSeconds()*_speed;
	if (step > dist)
	{
		if (_checkpoint.front() != _goal)
		{
			_checkpoint.push(_checkpoint.front()->getDirectionTo(_goal));
		}
		_checkpoint.pop();
	}
	direction.x*=step/dist;
	direction.y*=step/dist;
	sf::CircleShape::move(direction);
	return false;
}
