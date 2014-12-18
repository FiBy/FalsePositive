#include "Engine/Person.hpp"

Person::Person(Map* map, MapComponent* spawn,
			   std::vector<Person*>* all,
			   MapComponent* goal, float speed) :
	_acceleration(2048.0f),
	_allpersons(all),
	_ct(spawn),
	_goal(goal),
	_map(map),
	_speed(speed)
{
	setRadius(_radius);
	setPosition(spawn->getCenter()-sf::Vector2f(getRadius(),getRadius()));
	_pos = getPosition() + sf::Vector2f(getRadius(),getRadius());
	setFillColor(sf::Color::Red);

	_checkpoint.push(spawn->getDirectionTo(goal));
	_direction = _checkpoint.back()->getCenter() - _pos;
	_direction = _direction/sfe::length(_direction)*_speed;
}

Person::movement Person::move(sf::Time elapsed)
{
	if (_checkpoint.empty())
	{
		return movement::none;
	}
	float acceleration = _acceleration*elapsed.asSeconds();
	movement mv = movement::moved;
	sf::Vector2f drag	= _checkpoint.back()->getCenter() - _pos;
	float dist = sfe::length(drag);
	drag = drag/dist*acceleration;
	for (Person* p : *_allpersons)
	{
		if (p != this)
		{
			dist = sfe::length(getPosition() - p->getPosition());
				sf::Vector2f dodge;
				dodge = (_pos - p->_pos);
				dodge = dodge/sfe::length(dodge)*0.75f
						/powf((dist-2*_radius)/_radius,2)*acceleration;
				drag += dodge;
		}
	}
	std::pair<bool,sf::Vector2f> walldodge_ct = _ct->getForce(_pos,
															  _direction,
															  _checkpoint.front(),
															  _radius);
	if (walldodge_ct.first)
	{
		_direction = sf::Vector2f(0,0);
		drag = walldodge_ct.second*acceleration;
	}
	else
	{
		drag += walldodge_ct.second*acceleration;
	}
	_direction += drag;
	if (sfe::length(_direction) > _speed)
	{
		_direction = _direction/sfe::length(_direction)*_speed;
	}
	sf::CircleShape::move(_direction*elapsed.asSeconds());
	_pos = getPosition() + sf::Vector2f(getRadius(),getRadius());

	if (*_checkpoint.front() == _pos)
	{
		#ifdef DEBUG
		if (getFillColor() == sf::Color::Red)
		{
			setFillColor(sf::Color::Yellow);
		}
		else
		{
			setFillColor(sf::Color::Red);
		}
		#endif
		_ct = _checkpoint.front();
		if ( _ct != _goal)
		{
			_checkpoint.push(_map->getAStarPath(_ct,_goal).front());
		}
		_checkpoint.pop();
		mv = movement::arrived;
	}
	#ifdef DEBUG
	if (*_ct != _pos)
	{
		setFillColor(sf::Color::Blue);
	}
	#endif
	return mv;
}
