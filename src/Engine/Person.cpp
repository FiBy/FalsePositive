#include "Engine/Person.hpp"

Person::Person(Map* map, MapComponent* spawn,
			   std::vector<Person*>* all,
			   MapComponent* goal, float speed) :
	_allpersons(all),
	_ct(spawn),
	_goal(goal),
	_map(map),
	_speed(speed)
{
	setRadius(_radius);
	setPosition(spawn->getCenter()-sf::Vector2f(getRadius(),getRadius()));
	setFillColor(sf::Color::Red);

	_checkpoint.push(spawn->getDirectionTo(goal));
}

Person::movement Person::move(sf::Time elapsed)
{
	if (_checkpoint.empty())
	{
		return movement::none;
	}
	movement mv = movement::moved;
	sf::Vector2f direction	= _checkpoint.front()->getCenter()
							- getPosition()
							- sf::Vector2f(getRadius(),getRadius());
	float dist = _len(direction);
	float step = elapsed.asSeconds()*_speed;
	if (step > dist)
	{
		_ct = _checkpoint.front();
		if ( _ct != _goal)
		{
			_checkpoint.push(_map->getAStarPath(_ct,_goal,1)[0]);
		}
		_checkpoint.pop();
		mv = movement::arrived;
	}
	direction.x*=step/dist;
	direction.y*=step/dist;
	for (Person* p : *_allpersons)
	{
		if (p != this)
		{
			dist = _len(getPosition()+direction - p->getPosition());
			if ( dist < 4*_radius)
			{
				sf::Vector2f rotdirect;
				rotdirect.x = direction.x*std::cos(_rotationangle)
							- direction.y*std::sin(_rotationangle);
				rotdirect.y = direction.x*std::sin(_rotationangle)
							+ direction.y*std::cos(_rotationangle);
				direction = rotdirect;
				sf::CircleShape::move(direction);
				return mv;
			}
		}
	}
	sf::CircleShape::move(direction);
	return mv;
}
