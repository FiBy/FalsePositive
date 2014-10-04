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
	_direction = _direction/sfe::lenght(_direction)*_speed;
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
	float dist = sfe::lenght(drag);
	drag = drag/dist*acceleration;
	for (Person* p : *_allpersons)
	{
		if (p != this)
		{
			dist = sfe::lenght(getPosition() - p->getPosition());
			if ( dist < 8*_radius )
			{
				if (sfe::scalar(_direction,p->_direction) < 0)
				{
					drag = 0.25f*drag;
					sf::Vector2f dodge;
					dodge = sfe::normal(getPosition(),p->getPosition())[0];
					dodge = dodge/sfe::lenght(dodge)*0.75f
							/powf((dist-2*_radius)/_radius,2)*acceleration;
					drag += dodge;
				}
				else if (dist < 4*_radius)
				{
					drag = 0.25f*drag;
					sf::Vector2f dodge;
					dodge =  _pos - p->_pos;
					dodge = dodge/sfe::lenght(dodge)*0.75f
							/powf((dist-2*_radius)/_radius,2)*acceleration;
					drag += dodge;
				}
			}
		}
	}
	std::pair<bool,sf::Vector2f> walldodge_ct = _ct->getForce(_pos,_radius);
	if (walldodge_ct.first)
	{
		_direction = sf::Vector2f(0,0);
		drag = walldodge_ct.second*acceleration;
	}
	else
	{
		drag += walldodge_ct.second*acceleration;
		drag += _checkpoint.front()->getForce(_pos,_radius).second*acceleration;
	}
	_direction += drag;
	if (sfe::lenght(_direction) > _speed)
	{
		_direction = _direction/sfe::lenght(_direction)*_speed;
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
