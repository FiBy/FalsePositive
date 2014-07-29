#ifndef PERSON_HPP
#define PERSON_HPP

#include <SFML/Graphics.hpp>

#include "Engine/MapPortal.hpp"

class Person : public sf::CircleShape
{
public:
	Person(MapPortal* spawn, MapPortal* goal);
};

#endif // PERSON_HPP
