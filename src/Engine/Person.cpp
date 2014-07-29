#include "Engine/Person.hpp"

Person::Person(MapPortal* spawn, MapPortal* goal)
{
	setPosition(spawn->getCenter());
}
